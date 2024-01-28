#include "../include/file.h"

#include <stdbool.h>
#include <stdio.h>

#include "../include/lines.h"
#include "../include/error.h"

Error check_file(FILE* file, Lines* lines, int rule) {
    if (!file) {
        return INVALID_FILE;
    }
    
    int line_length = 0;
    int c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            if (line_length > rule) {
                if (add_line(lines, lines->total_lines) != OK) {
                    return ALLOCATION_ERROR;
                }
            }
            line_length = 0;
            lines->total_lines++;
        } else {
            line_length++;
        }
    }
    return OK;
}
