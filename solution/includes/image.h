#ifndef _IMAGE_H
#define _IMAGE_H
#include "mm_malloc.h"
#include "stdbool.h"
#include "stdint.h"

enum read_status {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER,
    READ_ERROR
};

enum write_status  {
    WRITE_OK = 0,
    WRITE_ERROR
};


struct __attribute__ ((packed)) pixel {
    uint8_t r, g, b;
};

struct image {
    uint32_t width;
    uint32_t height;
    struct pixel * data;
};

struct image create_image (uint32_t width, uint32_t height);
void destroy_img (struct image * img);
bool set_pixel (struct image * img, struct pixel px, uint32_t h, uint32_t w);
struct pixel get_pixel (const struct image * img, uint32_t h, uint32_t w);
#endif
