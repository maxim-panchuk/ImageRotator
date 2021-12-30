
#include "../includes/rotation.h"
/*struct image rotate_manager (const struct image source) {
    struct image rotated_img = create_image(source.height, source.width);
    for (size_t i = 0; i < source.height; i++) {
        for (size_t j = 0; j < source.width; j++) {
            set_pixel(&rotated_img, get_pixel(&source, j, source.height - i - 1), i, j);
        }
    }
    return rotated_img;
}*/

struct image rotate (const struct image * source ) {
    struct image out = create_image(source->height, source->width);
    for (size_t i = 0; i < out.height; i++) {
        for (size_t j = 0; j < out.width; j++) {
            out.data[i * out.width + j] =  source->data[(source->height - j - 1) * source->width + i];
        }
    }
    return out;
}




