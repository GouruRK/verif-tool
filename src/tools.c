#include "../include/tools.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>

int max(int a, int b) {
    return a < b ? b: a;
}

/**
 * @brief Check if path's type is the masked
 * 
 * @param path path to check
 * @param mask expected value
 * @return true if path's type is equals to the mask
 * @return else false
 */
static bool check_path_status(const char* path, int mask) {
    struct stat path_stat;
    if (stat(path, &path_stat)) {
        return false;
    }
    return __S_ISTYPE(path_stat.st_mode, mask);
}

bool is_file(const char* path) {
    return check_path_status(path, __S_IFREG);
}

bool is_directory(const char* path) {
    return check_path_status(path, __S_IFDIR);
}

bool is_alpha_num(int c) {
    return ('a' <= c && c <= 'z')
        || ('A' <= c && c <= 'Z')
        || ('1' <= c && c <= '9');
}
