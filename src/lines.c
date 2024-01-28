#include "../include/lines.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "../include/error.h"

Error init_lines(Lines* lines) {
    lines->lines = (int*)malloc(sizeof(int)*DEFAULT_LINES_LENGTH);
    if (!(lines->lines)) {
        return ALLOCATION_ERROR;
    }
    lines->max_lines_length = DEFAULT_LINES_LENGTH;
    lines->cur_lines_length = 0;
    lines->total_lines = 1;
    return OK;
}

/**
 * @brief Realloc lines array
 * 
 * @param lines lines collection to realloc
 * @return ALLOCATION_ERROR if error while allocating memory
 * @return OK
 */
static Error realloc_lines(Lines* lines) {
    if (lines->cur_lines_length != lines->max_lines_length) {
        return OK;
    }

    int pattern = lines->max_lines_length + DEFAULT_LINES_LENGTH;
    int* temp = realloc(lines->lines, sizeof(int)*pattern);
    if (!temp) {
        free_lines(lines);
        return ALLOCATION_ERROR;
    }

    lines->lines = temp;
    lines->max_lines_length += DEFAULT_LINES_LENGTH;
    return OK;
}

Error add_line(Lines* lines, int line) {
    if (realloc_lines(lines) != OK) {
        return ALLOCATION_ERROR;
    }
    lines->lines[lines->cur_lines_length++] = line;
    return OK;
}

void reset_lines(Lines* lines) {
    lines->cur_lines_length = 0;
    lines->total_lines = 1;
}

void free_lines(Lines* lines) {
    free(lines->lines);
}
