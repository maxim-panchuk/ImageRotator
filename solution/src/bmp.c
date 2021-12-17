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

static bool validate_header (const struct bmp_header header) {
    return header.bfType == 0x4D42;
}

static bool write_offset (FILE * file, uint32_t width) {
    int8_t z = 0;
    for (size_t i = 0; i < calc_padding(width); i++) {
        if (!fwrite(&z, sizeof (int8_t), 1, file)) return false;
    }
    return true;
}

static bool to_image (FILE * file, const struct bmp_header header, struct image * img) {
    *img = define_image(header.biWidth, header.biHeight);
    fseek(file, header.bOffBits, SEEK_SET);
    for (uint32_t i = 0; i < img->height; i++) {
        for (uint32_t j = 0; j < img->width; j++) {
            struct pixel px = {0};
            if (!fread(&px, sizeof (struct pixel), 1, file)) {
                destroy(img);
                return false;
            }
            set_pixel(img, px, j, i);
        }
        if ((img->width) * 3 % 4) {
            fseek(file, calc_padding(img->width), SEEK_CUR);
        }

    }
    return true;
}

static struct bmp_header create_bmp_header (const struct image * img) {
    struct bmp_header header = {0};
    header.bfType = 0x4D42;
    header.bfileSize = sizeof (struct bmp_header) + img->width * img->height * sizeof(struct pixel)
            + img->height * calc_padding(img->width);
    header.bOffBits = 54;
    header.biSize = 40;
    header.biWidth = img->width;
    header.biHeight = img->height;
    header.biPlanes = 1;
    header.biBitCount = 24;
    header.biSizeImage = header.bfileSize - 54;
    return header;

}

enum read_status from_bmp( FILE* in, struct image* img ) {
    if (!in) return FILE_NOT_FOUND;
    struct bmp_header head = {0};
    if (!fread(&head, sizeof(struct bmp_header), 1, in)) return READ_INVALID_HEADER;
    if (!validate_header(head)) return READ_INVALID_SIGNATURE;
    if (!to_image(in, head, img)) return READ_INVALID_BITS;
    return READ_OK;
}

enum write_status to_bmp( FILE* out, struct image const* img ) {
    struct bmp_header header = create_bmp_header(img);
    if (!fwrite(&header, sizeof (struct bmp_header), 1, out)) return WRITE_ERROR;
    for (uint32_t i = 0; i < img->height; i++) {
        for (uint32_t j = 0; j < img->width; j++) {
            struct pixel px = get_pixel(img, j, i);
            if (!fwrite(&px, sizeof (struct pixel), 1, out)) return WRITE_ERROR;
        }
        if (!write_offset(out, img->width)) return WRITE_ERROR;
    }
    return WRITE_OK;
}




