#include "../includes/rotation.h"

struct image rotate (const struct image * source) {
    struct image rotated_img = create_image(source->height, source->width);
    for (size_t i = 0; i < rotated_img.height; i++) {
        for (size_t j = 0; j < rotated_img.width; j++) {
            set_pixel(&rotated_img, get_pixel(source, source->height - j - 1, i), i, j);
        }
    }
    return rotated_img;
}
