#ifndef _UTIL_H
#define _UTIL_H

#include "bmp.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>


enum open_status {
    OPEN_OK = 0,
    OPEN_FAILED
};

enum save_status {
    SAVED_OK = 0,
    SAVING_FAILED
};

enum open_status open_file (const char * path_to_file, FILE ** file);
enum save_status save_file (const char * path_to_file, FILE ** file);

_Noreturn void err (const char * msg, ... );

#endif
