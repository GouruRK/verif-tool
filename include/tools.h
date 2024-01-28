#ifndef TOOLS_H
#define TOOLS_H

#include <stdbool.h>

/**
 * @brief Get maximum value between `a` and `b`
 * 
 * @param a 
 * @param b 
 * @return
 */
int max(int a, int b);

/**
 * @brief Check if given path is a file
 * 
 * @param path path to check
 * @return true if path is a file
 * @return else false
 */
bool is_file(const char* path);

/**
 * @brief Check if given path is a directory
 * 
 * @param path path to check
 * @return true if path is a directory
 * @return else false
 */
bool is_directory(const char* path);

/**
 * @brief Check if character is alphabetic or numeric
 * 
 * @param c character to check
 * @return true if character is alphabetic or numeric
 * @return else false
 */
bool is_alpha_num(int c);

#endif
