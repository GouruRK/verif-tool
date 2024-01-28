#include "../include/extensions.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "../include/error.h"
#include "../include/tools.h"

/**
 * @brief Count number of extensions contains in the source string
 * 
 * @param src source string
 * @param longest_ext set to the longest extension in characters
 * @return number of extensions contains in the source string
 */
static int count_extensions(const char* src, int* longest_ext) {
    *longest_ext = -1;

    if (!src || src[0] == '\0') {
        return 0;
    }

    int res = 0, i = 0, start = 0;
    for (; src[i] != '\0'; i++) {
        // add an extension if we have a comma. A comma must not be the first
        // character. Then, check if the last character was also a comma, in
        // case of emtpy extensions
        if (src[i] == ',' && i && src[i - 1] != ',') {
            res++;
            *longest_ext = max(*longest_ext, i - start);
        }
        if (src[i] == ',') {
            start = i + 1;
        }
    }
    // add an extension if sources does not finish by a comma
    // cannot jump because of first condition
    if (src[i - 1] != ',') {
        res++;
        *longest_ext = max(*longest_ext, i - start);
    }
    return res;
}

/**
 * @brief Fill extension collection from source string
 * 
 * @param src source
 * @param exts extension collection
 */
static void fill_extensions(const char* src, Extensions* exts) {
    int ext_index = 0, char_index = 0, i;

    for (i = 0; src[i] != '\0'; i++) {
        if (src[i] != ',') {
            exts->extensions[ext_index][char_index] = src[i];
            char_index++;
        } else if (i && src[i - 1] != ',') {
            exts->extensions[ext_index][char_index] = '\0';
            char_index = 0;
            ext_index++;

        }
    }
    if (src[i - 1] != ',') {
        exts->extensions[ext_index][char_index] = '\0';
    }
}

Error init_extensions_array(Extensions* exts, int nb_exts, int longest_ext) {
    exts->extensions = (char**)malloc(sizeof(char*)*nb_exts);
    if (!(exts->extensions)) {
        return ALLOCATION_ERROR;
    }

    int malloc_len = sizeof(char) * (longest_ext + 1);
    exts->nb_exts = 0;
    for (; exts->nb_exts < nb_exts; exts->nb_exts++) {
        exts->extensions[exts->nb_exts] = (char*)malloc(malloc_len);
        if (!(exts->extensions[exts->nb_exts])) {
            free_extensions(exts);
            return ALLOCATION_ERROR;
        }
    }
    return OK;
}

Error init_extensions(const char* src, Extensions* exts) {
    int longest_ext;
    int nb_exts = count_extensions(src, &longest_ext);
    
    if (!(nb_exts)) {
        exts->none = true;
        return OK;
    } else {
        exts->none = false;
    }
    
    if (init_extensions_array(exts, nb_exts, longest_ext) != OK) {
        return ALLOCATION_ERROR;
    }

    fill_extensions(src, exts);
    
    return OK;
}

/**
 * @brief Check if the extension `ext` is include in `file` name
 * 
 * @param file filename to check
 * @param ext extension name in filename
 * @param i start index in filename to begin the check (i - 1 == '.')
 * @return true if the extension is included
 * @return else false
 */
static bool is_include(const char* file, const char* ext, int i) {
    int j = 0;
    for (; ext[j] != '\0' && file[i] != '\0'; i++, j++) {

        if (file[i] != ext[j]) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Check if the filename contains extension from the extension collection
 * 
 * @param filename filename to check
 * @param exts extension collection
 * @return true if the filename'extension is one of the researched one
 * @return else false
 */
bool is_extension_searched(const char* filename, Extensions* exts) {
    if (!filename) {
        return false;
    }
    if (exts->all) {
        return true;
    }
    for (int i = 0; filename[i] != '\0'; i++) {
        if (filename[i] == '.') {
            for (int j = 0; j < exts->nb_exts; j++) {
                // i + 1 because currently, filename[i] = '.'
                if (is_include(filename, exts->extensions[j], i + 1)) {
                    return true;
                }
                // no break because file's format could be 'file.a.b'
            }
        }
    }
    return false;
}

/**
 * @brief Free allocated memory for the extension collection
 * 
 * @param exts 
 */
void free_extensions(Extensions* exts) {
    if (exts && !(exts->none)) {
        for (int i = 0; i < exts->nb_exts; i++) {
            free(exts->extensions[i]);
        }
        free(exts->extensions);
    }
}
