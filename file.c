#include "file.h"

uint8_t *file_load (const char *file_s) {

    FILE *f_in = fopen(file_s, "r");
    if (! f_in) {
        fprintf(stderr, "Failed to open %s\n", file_s);
        return NULL;
    }

    fseek (f_in, 0, SEEK_END);
    uint32_t b_n = ftell (f_in);
    fseek (f_in, 0, SEEK_SET);

    uint8_t *_b = (uint8_t *) malloc(b_n);
    if (! _b) {
        fprintf(stderr, "Failed to malloc %u\n", b_n);
        return NULL;
    }

    if (fread(_b, 1, b_n, f_in) < b_n) {
        fprintf(stderr, "Failed to read %u\n", b_n);
        return NULL;
    }

    fclose (f_in);
 
    return _b;
}

