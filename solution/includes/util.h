#ifndef _UTIL_H
#define _UTIL_H
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

enum open_read_status {
    OPEN_READ_OK = 0,
    OPEN_READ_FAILED
};

enum open_write_status {
    OPEN_WRITE_OK = 0,
    OPEN_WRITE_FAILED
};

enum close_status {
    CLOSE_OK = 0,
    CLOSE_FAILED
};

_Noreturn void err (const char * msg, ... );
enum open_read_status read_file (const char * path_to_file, FILE ** file);
enum open_write_status write_file (const char * path_to_file, FILE ** file);
enum close_status close_file (FILE * file);
#endif
