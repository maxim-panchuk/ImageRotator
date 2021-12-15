#include "../includes/bmp.h"

struct __attribute__((packed)) bmp_header{
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

static uint32_t calc_padding (uint32_t width) {
    return 4 - ((width * 3) % 4);
}

static struct bmp_header create_bmp_header (struct bmp_header * header, const struct image * img) {
    header->bfType = 0x4D42;
    header->bfileSize = sizeof (struct bmp_header) + img->width * img->height * sizeof(struct pixel)
            + img->height * calc_padding(img->width);

}



enum read_status from_bmp( FILE* in, struct image* img ) {
    return READ_OK;
}

enum write_status to_bmp( FILE* out, struct image const* img ) {
    return WRITE_OK;
}



