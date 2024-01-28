#ifndef FILE_EXPLORER_H
#define FILE_EXPLORER_H

#include <stdbool.h>

#include "lines.h"
#include "error.h"
#include "extensions.h"

/**
 * @brief Store lines number where their length is larger that the rule in lines
 * 
 * @param path file
 * @param lines line collection
 * @param rule maximum line length
 * @param verbose always print file report
 * @return INVALID_FILE if file file cannot be read
 * @return ALLOCATION_ERROR if error while allocating memory
 * @return OK
 */
Error process_file(const char* path, Lines* lines, int rule, bool verbose);

/**
 * @brief Check files' lines in directory
 * 
 * @param path directory path
 * @param lines line collections
 * @param exts extension filter
 * @param rule maximum line length
 * @param verbose always print file report
 * @param recursive check sub directories
 * @return INVALID_DIRECTORY if directory cannot be read
 * @return ALLOCATION_ERROR if error while allocating memory
 * @return OK
 */
Error process_directory(const char* path, Lines* lines, Extensions* exts,
                        int rule, bool verbose, bool recursive);

#endif
