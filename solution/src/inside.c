#include "../includes/inside.h"
#include <stdlib.h>

struct image define_image (uint32_t width, uint32_t height) {
    struct image img = {0};
    img.width = width;
    img.height = height;
    img.data = malloc (width * height * sizeof (struct pixel));
    return img;
}

void destroy (struct image * img) {
    free(img->data);
}

bool set_pixel (struct image* img, struct pixel px, uint32_t x, uint32_t y) {
    if (x < img->width && y < img->height) {
        img->data[y * img->width + x] = px;
        return true;
    }
    return false;
}

struct pixel get_pixel (const struct image* img, uint32_t x, uint32_t y) {
    return img->data[y * img->width + x];
}

