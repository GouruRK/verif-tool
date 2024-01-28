#include <stddef.h>
#include <stdio.h>

#include "../include/extensions.h"
#include "../include/command_line.h"
#include "../include/error.h"
#include "../include/tools.h"
#include "../include/lines.h"
#include "../include/file_explorer.h"
#include "../include/io.h"

int main(int argc, char* argv[]) {
    Arguments args = init_args();
    Error err = parse_command_line(&args, argc, argv);
    if (err != OK) {
        print_error(err);
        return 1;
    }
    if (args.help) {
        print_help();
        return 0;
    }
    Lines lines;
    if ((err = init_lines(&lines)) != OK) {
        print_error(err);
        return 1;
    }

    if (is_file(args.start_path)) {
        err = process_file(args.start_path, &lines, args.rule, args.verbose);
    } else if (is_directory(args.start_path)) {
        err = process_directory(args.start_path, &lines, &args.exts, args.rule,
                             args.verbose, args.recursive);
    } else {
        print_error(UNKNOWN_PATH);
    }

    free_extensions(&args.exts);
    free_lines(&lines);
    return 0;
}
