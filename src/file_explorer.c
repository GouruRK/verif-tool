#include "../include/file_explorer.h"

#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#include "../include/lines.h"
#include "../include/error.h"
#include "../include/file.h"
#include "../include/io.h"
#include "../include/tools.h"

Error process_file(const char* path, Lines* lines, int rule, bool verbose) {
    FILE* file = fopen(path, "r");
    if (!file) {
        return INVALID_FILE;
    }
    Error err;
    if ((err = check_file(file, lines, rule)) != OK) {
        return err;
    }
    print_file_report(path, lines, verbose);
    reset_lines(lines);
    fclose(file);
    return OK;
}

/**
 * @brief Concat two path and add a '/' between them
 * 
 * @param path source path
 * @param to_add path to add
 * @return new path
 */
static char* smash_path(const char* path, const char* to_add) {
    int path_len = strlen(path);
    int new_len = path_len + strlen(to_add) + 2;
    char* smashed_path = (char*)malloc(sizeof(char)*new_len);
    if (!smashed_path) {
        return NULL;
    }


    strcpy(smashed_path, path);
    if (path[0] != '/') {
        smashed_path[path_len] = '/';
        smashed_path[path_len + 1] = '\0';
    }
    strcat(smashed_path, to_add);
    return smashed_path;
}

Error process_directory(const char* path, Lines* lines, Extensions* exts,
                        int rule, bool verbose, bool recursive) {
    DIR* dir = opendir(path);
    if (!dir) {
        printf("%s\n", path);
        return INVALID_DIRECTORY;
    }

    struct dirent* dir_handle;
    while ((dir_handle = readdir(dir)) != NULL) {
        if (dir_handle->d_name[0] == '.') {
            continue;
        }

        char* ressource_path = smash_path(path, dir_handle->d_name);
        if (!ressource_path) {
            closedir(dir);
            return ALLOCATION_ERROR;
        }

        if (is_directory(ressource_path) && recursive) {
            Error err;
            err = process_directory(ressource_path, lines, exts, rule, verbose,
                                    recursive);
            if (err != OK) {
                closedir(dir);
                return err;
            }
        } else if (is_file(ressource_path) 
                    && is_extension_searched(ressource_path, exts)) {
            process_file(ressource_path, lines, rule, verbose);
        }
        free(ressource_path);
    }

    closedir(dir);
    return OK;
}
