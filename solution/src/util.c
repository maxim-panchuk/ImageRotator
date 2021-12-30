#include "../includes/util.h"

_Noreturn void err (const char * msg, ... ) {
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
    exit(1);
}

enum open_read_status read_file (const char * path_to_file, FILE ** file) {
    if ((*file = fopen(path_to_file, "rb")) == NULL) return OPEN_READ_FAILED;
    return OPEN_READ_OK;
}

enum open_write_status write_file (const char * path_to_file, FILE ** file) {
    if ((*file = fopen(path_to_file, "wb")) == NULL) return OPEN_WRITE_FAILED;
    return OPEN_WRITE_OK;
}

enum close_status close_file (FILE * file) {
    if (fclose(file)) return CLOSE_FAILED;
    return CLOSE_OK;
}




