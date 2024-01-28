#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include <stdbool.h>
#include "extensions.h"

/**
 * @brief Contains arguments given from command lines
 * 
 */
typedef struct {
    bool recursive;
    bool help;
    bool verbose;
    int rule;
    char* start_path;
    Extensions exts;
} Arguments;

/**
 * @brief Set default values for command line parameters
 * 
 * @return default Arguments
 */
Arguments init_args(void);

/**
 * @brief Parse command line given parameters
 * 
 * @param args store parameters, contains default values
 * @param argc number of parameters and options
 * @param argv parameters
 * @return
 */
Error parse_command_line(Arguments* args, int argc, char* argv[]);

#endif
