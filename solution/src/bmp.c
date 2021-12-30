#include "../includes/bmp.h"

static bool is_bmp_header (struct bmp_header header) {
    return header.bfType == 0x4D42;
}

static bool nz_padding (const struct image * img) {
    return (img->width * 3) % 4;
}

static uint32_t calc_padding (const struct image * img) {
    return 4 - ((img->width * 3) % 4);
}

static bool write_padding (FILE * out, const struct image * img) {
    int8_t z = 0;
    for (size_t i = 0; i < calc_padding(img); i++) {
        if (!fwrite(&z, sizeof (int8_t), 1, out)) return false;
    }
    return true;
}

static uint32_t calc_file_size (const struct image * img) {
    return sizeof (struct bmp_header) + img->width * img->height * sizeof(struct pixel)
           + img->height * calc_padding(img);
}

static bool to_image (FILE * file, const struct bmp_header header, struct image * img) {
    *img = create_image(header.biWidth, header.biHeight);
    fseek(file, header.bOffBits, SEEK_SET);
    for (uint32_t i = 0; i < img->height; i++) {
        for (uint32_t j = 0; j < img->width; j++) {
            struct pixel px = {0};
            if (!fread(&px, sizeof(struct pixel), 1, file)) {
                destroy_img(img);
                return false;
            }
            set_pixel(img, px, i, j);
        }
        if (nz_padding(img)) fseek(file, calc_padding(img), SEEK_CUR);
    }
    return true;
}

static struct bmp_header create_bmp_header (const struct image * img) {
    return (struct bmp_header) {
        .bfType = 0x4D42,
        .bfileSize = calc_file_size(img),
        .bOffBits = 54,
        .biSize = 40,
        .biWidth = img->width,
        .biHeight = img->height,
        .biPlanes = 1,
        .biBitCount = 24,
        .biSizeImage = calc_file_size(img) - 54,
    };
}

enum read_status from_bmp (FILE * in, struct image * img) {
    if (!in) return READ_ERROR;
    struct bmp_header header = {0};
    if (!fread(&header, sizeof (struct bmp_header), 1, in)) return READ_INVALID_HEADER;
    if (!is_bmp_header(header)) return READ_INVALID_SIGNATURE;
    if (!to_image(in, header, img)) return READ_INVALID_BITS;
    return READ_OK;
}

enum write_status to_bmp (FILE * out, const struct image * img) {
    if (!out) return WRITE_ERROR;
    struct bmp_header header = create_bmp_header(img);
    if (!fwrite(&header, sizeof (struct bmp_header), 1, out)) return WRITE_ERROR;
    for (uint32_t i = 0; i < header.biHeight; i++) {
        for (uint32_t j = 0; j < header.biWidth; j++) {
            struct pixel px = get_pixel(img, i, j);
            if (!fwrite(&px, sizeof (struct pixel), 1, out)) return WRITE_ERROR;
        }
        if (nz_padding(img)) {
            if (!write_padding(out, img)) return WRITE_ERROR;
        }
    }
    return WRITE_OK;
}