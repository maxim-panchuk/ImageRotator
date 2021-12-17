#ifndef _BMP_H
#define _BMP_H

#include "inside.h"
#include "stdio.h"


enum read_status  {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER,
    FILE_NOT_FOUND
};

enum  write_status  {
    WRITE_OK = 0,
    WRITE_ERROR
};

enum read_status from_bmp( FILE* in, struct image* img );

enum write_status to_bmp( FILE* out, struct image const* img );

#endif

