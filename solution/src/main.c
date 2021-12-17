#include "../includes/rotate.h"
#include "../includes/util.h"
#include <stdio.h>


void usage () {
    fprintf(stderr, "Usage: ./build/image-transformer \n");
}

int main( int argc, char** argv ) {
    if (argc != 3) usage();
    if (argc < 3) err("Not enough arguments \n");
    if (argc > 3) err("Too many arguments \n");

    FILE * file;

    FILE * out_file;

    if (open_file(argv[1], &file) != 0) err("Failed to open file \n");
    struct image img = {0};

    switch (from_bmp(file, &img)) {
        case 4:
            err("File not found \n");
            break;
        case 1:
            err("Invalid signature \n");
            break;
        case 2:
            err("Invalid bits \n");
            break;
        case 3:
            err("Invalid header \n");
            break;
        case 0:
            break;
    }

    struct image rotated_img = rotate(img);
    if (save_file(argv[2], &out_file) != 0) err("Failed to open destination file \n");
    if (to_bmp(out_file, &rotated_img) != 0) err("Failed to transform file \n");

    fclose(file);
    fclose(out_file);
}
