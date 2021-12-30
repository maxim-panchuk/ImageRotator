#include "../includes/image.h"

struct image create_image (uint32_t width, uint32_t height) {
    struct image img = {0};
    img.width = width;
    img.height = height;
    img.data = malloc (width * height * sizeof (struct pixel));
    return img;
}

void destroy_img (struct image * img) {
    free(img->data);
}

bool set_pixel (struct image * img, struct pixel px, uint32_t h, uint32_t w) {
    if (w < img->width && h < img->height) {
        img->data[h * img->width + w] = px;
        return true;
    }
    return false;
}

struct pixel get_pixel (const struct image * img, uint32_t h, uint32_t w) {
    return img->data[h * img->width + w];
}


