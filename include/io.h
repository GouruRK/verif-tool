#ifndef IO_H
#define IO_H

#include <stdbool.h>

#include "lines.h"

// colors
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define PURPLE "\x1b[35m"
#define CYAN "\x1b[36m"
#define UNDERLINE "\e[4m"
#define BOLD "\e[1m"
#define RESET "\x1b[0m"

/**
 * @brief Print file report
 * 
 * @param path file path
 * @param lines line collection
 * @param verbose always print report
 */
void print_file_report(const char* path, Lines* lines, bool verbose);

/**
 * @brief Print help message
 * 
 */
void print_help(void);

/**
 * @brief Print error message according to the code
 * 
 * @param code error code
 */
void print_error(Error code);

#endif
