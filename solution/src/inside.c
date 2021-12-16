#include "..includes/inside.h"

struct image define_image (uint32_t width, uint32_t height) {
    struct image img = {0};
    img.width = width;
    img.height = height;
    img.data = malloc(width * height * sizeof (struct pixel));
    return img;
}

