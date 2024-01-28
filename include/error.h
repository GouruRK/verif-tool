#ifndef ERROR_H
#define ERROR_H

/**
 * @brief Enumeration of possible error at runtime
 * 
 */
typedef enum {
    OK,
    ALLOCATION_ERROR,
    INVALID_RULE,
    INVALID_DIRECTORY,
    INVALID_FILE,
    NO_EXTENSION_FOUND,
    UNKNOWN_PATH
} Error;

#endif
