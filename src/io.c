#include "../include/io.h"

#include <stdio.h>
#include <stdbool.h>

#include "../include/lines.h"

void print_file_report(const char* path, Lines* lines, bool verbose) {
    static int printed_file = 0; // separation between each report
    if (verbose || lines->cur_lines_length) {

        if (printed_file) { // prevent new line when first report is print
            putchar('\n');
        }
        printed_file++;
        printf("%s%s%s%s: \n", BOLD, UNDERLINE, path, RESET);
        if (lines->cur_lines_length == 0) {
            if (verbose) {
                printf("No line is too long !\n");
            }
        } else {
            for (int i = 0; i < lines->cur_lines_length; i++) {
                printf("Line %s%d%s is too long\n", CYAN, lines->lines[i],
                       RESET);
            }
            char* to_print = lines->cur_lines_length == 1 ? "line": "lines";
            printf("%s%d%s %s out of %s%d%s is too long\n", CYAN,
                   lines->cur_lines_length, RESET, to_print, GREEN,
                   lines->total_lines, RESET);
        }
    }
}

void print_help(void) {
    printf("Usage: verif [OPTION...] PATH\n"
           "Print lines number of file pointed by PATH that are too long\n"
           "according to the ruleset\n\n"
           "If PATH is a directory, it will check the files in "
            "that directory\n\n"
           "  -r, --recursive\tIf PATH contains directories, "
            "their content\n\t\t\t  will be checked too\n"
           "  -v, --verbose\t\tPrint file name even if file format is correct\n"
           "  -a, --all\t\tCheck all types of files. Overrides the filter"
            " parameter\n"
           "  -l, --length\t\tSpecify maximum line length. Default: 80\n"
           "  -f, --filter\t\tSpecify file type to check. Extensions must"
            " be separated\n\t\t\t  by a comma. Default extensions are"
            ".c and .h files\n"
           "  -h, --help\t\tPrint this message and exit\n"
           );
}

/**
 * @brief Array of error messages
 * 
 */
static char* err_msg[] = {
    [ALLOCATION_ERROR] = "allocation error",
    [INVALID_RULE] = "rule must be a valid positive integer",
    [INVALID_DIRECTORY] = "directory not found, or bad permissions",
    [INVALID_FILE] = "file not found, or bad permissions",
    [NO_EXTENSION_FOUND] = "no extension found",
    [UNKNOWN_PATH] = "no file or directory at given path"
};

void print_error(Error code) {
    if (code == OK) {
        return;
    }
    fprintf(stderr, "verif: %sError%s - %s\n", RED, RESET, err_msg[code]);
}
