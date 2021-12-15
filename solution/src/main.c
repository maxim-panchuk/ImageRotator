#include <stdio.h>
#include "../includes/util.h"

void usage () {
    fprintf(stderr, "Usage: ./build/image-transformer \n");
}

int main( int argc, char** argv ) {
    if (argc != 3) usage();
    if (argc < 3) err("Not enough arguments \n");
    if (argc > 3) err("Too many arguments \n");

    FILE * file;

    if (open_file(argv[1], &file) != 0) err("Failed to open file \n");
    struct image img = {0};
    if (from_bmp(file, &img) != 0) err("Failed to read file \n");



}
