#include "../includes/rotate.h"

struct image rotate (const struct image source) {
    struct image rotated_img = define_image(source.height, source.width);
    for (size_t i = 0; i < source.height; i++) {
        for (size_t j = 0; j < source.width; j++) {
            set_pixel(&rotated_img, get_pixel(&source, j, source.height - i - 1), i, j);
        }
    }
    return rotated_img;
}