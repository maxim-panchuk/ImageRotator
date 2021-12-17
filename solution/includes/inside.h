#ifndef _INSIDE_H
#define _INSIDE_H

#include <mm_malloc.h>
#include <stdint.h>
#include <stdbool.h>


struct image {
    uint64_t width, height;
    struct pixel * data;
};

struct pixel {
    uint8_t r, g, b;
};

struct image define_image (uint32_t width, uint32_t height);
bool set_pixel (struct image* img, struct pixel px, uint32_t x, uint32_t y);
struct pixel get_pixel (const struct image* img, uint32_t x, uint32_t y);
#endif
