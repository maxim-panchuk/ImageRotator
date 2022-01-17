#ifndef _BMP_H
#define _BMP_H

#include "image.h"
#include "stdio.h"
#include <stdbool.h>

enum read_status from_bmp(FILE * in, struct image * img );
enum write_status to_bmp(FILE * out, struct image const * img );
#endif
