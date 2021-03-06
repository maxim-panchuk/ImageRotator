#include "../includes/bmp.h"
#include "../includes/rotation.h"
#include "../includes/util.h"

void usage () {
    fprintf(stderr, "Usage: ./build/image-transformer \n");
}

int main (int argc, char ** argv) {
    if (argc != 3) usage();
    if (argc < 3) err("Not enough arguments \n");
    if (argc > 3) err("Too many arguments \n");

    FILE * source_file;
    FILE * destination_file;
    if (read_file(argv[1], &source_file) != READ_OK) err("can't open source file \n");
    if (write_file(argv[2], &destination_file) != READ_OK) err("can't open destination file \n");

    struct image img = {0};
    switch (from_bmp(source_file, &img)) {
        case READ_INVALID_BITS: {
            fprintf(stderr, "Invalid bits\n");
            close_file(source_file);
            return 1;
        }
        case READ_INVALID_SIGNATURE: {
            fprintf(stderr, "Invalid bmp signature\n");
            close_file(source_file);
            return 1;
        }
        case READ_INVALID_HEADER: {
            fprintf(stderr, "Invalid bmp header\n");
            close_file(source_file);
            return 1;
        }
        case READ_ERROR: {
            fprintf(stderr, "Can't open file \n");
            close_file(source_file);
            return 1;
        }
        case READ_OK: {
            break;
        }
    }
    if(close_file(source_file) != READ_OK) {
        fprintf(stderr, "Error while trying to close the file '\n");
        destroy_img(&img);
        return 1;
    }
    struct image new_img = rotate(&img);
    to_bmp(destination_file, &new_img);
    destroy_img(&new_img);
    destroy_img(&img);
    return 0;
}

