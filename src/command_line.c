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

/**
 * @brief Count extensions from file separated by non alpha numeric symbols
 * 
 * @param file file to check
 * @param longest_ext set to the longest extension in character
 * @return number of extensions
 */
static int count_extensions(FILE* file, int* longest_ext) {
    *longest_ext = -1;

    int c, index = 0, cnt = 0;
    while ((c = fgetc(file)) != EOF) {
        if (!is_alpha_num(c) && index) {
            *longest_ext = max(*longest_ext, index);
            cnt++;
        }
        if (!is_alpha_num(c)) {
            index = 0;
        } else {
            index++;
        }
    }
    if (index) {
        cnt++;
        *longest_ext = max(*longest_ext, index);
    }
    fseek(file, 0, SEEK_SET);
    return cnt;
}

/**
 * @brief Fill the extension collection from file
 * 
 * @param file source
 * @param exts extension collection
 */
static void fill_extensions(FILE* file, Extensions* exts) {
    int c, ext_index = 0, char_index = 0;
    while ((c = fgetc(file)) != EOF) {
        if (is_alpha_num(c)) {
            exts->extensions[ext_index][char_index++] = c;
        } else if (!is_alpha_num(c) && char_index) {
            exts->extensions[ext_index][char_index] = '\0';
            ext_index++;
            char_index = 0;
        }
    }
    if (char_index) {
        exts->extensions[ext_index][char_index] = '\0';
    }
}

/**
 * @brief Create an exension collection from config file
 * 
 * @param exts extension collection to initialise
 * @return NO_EXTENSION_FOUND if config file is empty or innexistant
 * @return ALLOCATION_ERROR if error while allocating memory
 * @return OK 
 */
static Error parse_extension_from_file(Extensions* exts) {
    FILE* file = fopen("config.txt", "r");
    if (!file) {
        return NO_EXTENSION_FOUND;
    }

    int longest_ext, cnt = count_extensions(file, &longest_ext);
    if (!cnt) {
        exts->none = true;
        return NO_EXTENSION_FOUND;
    } else {
        exts->none = false;
    }
    
    if (init_extensions_array(exts, cnt, longest_ext) != OK) {
        fclose(file);
        return ALLOCATION_ERROR;
    }

    fill_extensions(file, exts);
    fclose(file);
    return OK;
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
        return parse_extension_from_file(&(args->exts));
    }
    return OK;
}
