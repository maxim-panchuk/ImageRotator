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

struct image define_image (uint32_t width, uint32_t height);
#endif
