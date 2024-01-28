#ifndef LINES_H
#define LINES_H

#include "error.h"

#define DEFAULT_LINES_LENGTH 10

/**
 * @brief Line collection
 * 
 */
typedef struct {
    int max_lines_length;
    int cur_lines_length;
    int total_lines;
    int* lines;

} Lines;

/**
 * @brief Initialise given collection
 * 
 * @param lines collection to initialise
 * @return ALLOCATION_ERROR if error whille allocating memory
 * @return OK
 */
Error init_lines(Lines* lines);

/**
 * @brief Free allocated memory for collection
 * 
 * @param lines collection to free
 */
void free_lines(Lines* lines);

/**
 * @brief Add a line number to the collection
 * 
 * @param lines collection
 * @param line line number to add
 * @return ALLOCATION_ERROR if error whille allocating memory
 * @return OK
 */
Error add_line(Lines* lines, int line);

/**
 * @brief Set line collection to default values
 * 
 * @param lines 
 */
void reset_lines(Lines* lines);

#endif
