#ifndef _UTIL_H
#define _UTIL_H

#include "bmp.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>



enum open_status {
    OPEN_OK = 0,
    OPEN_FAILED
};

enum close_status {
    CLOSE_OK = 0,
    CLOSE_FAILED
};

enum open_status open_file (const char * path_to_file, FILE ** file);
_Noreturn void err (const char * msg, ... );

#endif
