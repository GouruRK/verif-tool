#ifndef FILE_H
#define FILE_H

#include <stdio.h>

#include "error.h"
#include "lines.h"

/**
 * @brief Add lines numbers of file to lines if their length is larger than 
 *        the rule 
 * 
 * @param file file to check
 * @param lines line collection
 * @param rule maximum line length
 * @return INVALID_FILE if file cannot be read
 * @return ALLOCATION_ERROR if error while allocating memory
 * @return OK
 */
Error check_file(FILE* file, Lines* lines, int rule);

#endif
