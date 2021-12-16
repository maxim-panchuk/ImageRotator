#include "../includes/util.h"

_Noreturn void err (const char * msg, ... ) {
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
    exit(1);
}

enum open_status open_file (const char * path_to_file, FILE ** file) {
    if ((*file = fopen(path_to_file, "rb")) == NULL) {
        return OPEN_FAILED;
    }
    return OPEN_OK;
}

enum save_status save_file (const char * path_to_file, FILE ** file) {
    if ((*file = fopen(path_to_file, "wb")) == NULL) return SAVING_FAILED;
    return SAVED_OK;
}


