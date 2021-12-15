#ifndef _INSIDE_H
#define _INSIDE_H
#include <stdint.h>

struct image {
    uint64_t width, height;
    struct pixel * data;
};

struct pixel {
    uint8_t r, g, b;
};
#endif
