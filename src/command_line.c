#include "../include/command_line.h"

#include <stdbool.h>
#include <stddef.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../include/extensions.h"
#include "../include/error.h"
#include "../include/tools.h"

Arguments init_args(void) {
    return (Arguments){
        .recursive = false,
        .help = false,
        .verbose = false,
        .rule = 80,
        .start_path = ".",
        .exts = (Extensions){
            .all = false,
            .nb_exts = 0
        }
    };
}

/**
 * @brief Convert string to integer
 * 
 * @param str string to convert
 * @param res set converted result
 * @return true if converted int is valid
 * @return else false
 */
static bool convert_int(const char* str, int* res) {
    char* err = NULL;
    *res = strtol(str, &err, 10);
    return !(*err || *res < 0);
}

Error parse_command_line(Arguments* args, int argc, char* argv[]) {
    int opt, opt_index = 0;
    
    static struct option long_options[] = {
        {"recursive", no_argument,       0, 'r'},
        {"help",      no_argument,       0, 'h'},
        {"verbose",   no_argument,       0, 'v'},
        {"all",       no_argument,       0, 'a'},
        {"length",    required_argument, 0, 'l'},
        {"filter",    required_argument, 0, 'f'},
        {0, 0, 0, 0}
    };
    while ((opt = getopt_long(argc, argv, "rhval:f:", long_options, &opt_index))
            != -1) {
        switch (opt) {
            case 'r':
                args->recursive = true;
                break;
            case 'h':
                args->help = true;
                return OK;
            case 'v':
                args->verbose = true;
                break;
            case 'a':
                args->exts.all = true;
                break;
            case 'l':
                if (!convert_int(optarg, &(args->rule))) {
                    free_extensions(&(args->exts));
                    return INVALID_RULE;
                }
                break;
            case 'f':
                if (args->exts.all) {
                    break;
                }
                if (init_extensions(optarg, &(args->exts)) != OK) {
                    return ALLOCATION_ERROR;
                }
                break;
            default:
                break;
        }
    }
    if (optind < argc) {
        args->start_path = argv[optind];
        int path_len = strlen(args->start_path);
        if (path_len != 1 && args->start_path[path_len - 1] == '/') {
            args->start_path[path_len - 1] = '\0';
        }
    }
    if (!args->exts.all && !args->exts.nb_exts) {
        if (init_extensions("c,h", &(args->exts)) != OK) {
            return ALLOCATION_ERROR;
        }
    }
    return OK;
}
