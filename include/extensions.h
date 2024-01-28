#ifndef EXTENSIONS_H
#define EXTENSIONS_H

#include <stdbool.h>

#include "error.h"

/**
 * @brief Contains extension the programm is searching to check
 * 
 */
typedef struct {
    bool all;
    bool none;
    int nb_exts;
    char** extensions;
} Extensions;

/**
 * @brief Init extension from string
 * 
 * @param src extensions to parse
 * @param exts extensions to initialise
 * @return ALLOCATION_ERROR
 * @return OK
 */
Error init_extensions(const char* src, Extensions* exts);

/**
 * @brief Init arrays for extensions
 * 
 * @param exts contains the arrays
 * @param nb_exts number of extensions
 * @param longest_ext longest extension in charater
 * @return ALLOCATION_ERROR
 * @return OK
 */
Error init_extensions_array(Extensions* exts, int nb_exts, int longest_ext);

/**
 * @brief Check if the given filename extension is in the extensiosn to search
 * 
 * @param filename filename to check
 * @param exts extensions collections
 * @return true if the filename extension is searched
 * @return else false
 */
bool is_extension_searched(const char* filename, Extensions* exts);

/**
 * @brief Free allocated memory for the extensions collection
 * 
 * @param exts collection to free
 */
void free_extensions(Extensions* exts);

#endif
