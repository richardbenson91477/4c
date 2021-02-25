#include "file.h"

uint8_t *file_load (const char *file_s) {
    printf("debug: file_load %s\n", file_s);

    FILE *f_in = fopen(file_s, "r");
    if (NULL == f_in) {
        fprintf(stderr, "error: file_load: fopen %s\n", file_s);
        return NULL;
    }

    fseek(f_in, 0, SEEK_END);
    uint32_t b_n = ftell(f_in);
    fseek(f_in, 0, SEEK_SET);

    if (0 == b_n) {
        fprintf(stderr, "error: file_load: empty file\n");
        fclose(f_in);
        return NULL;
    }

    uint8_t *_b = (uint8_t *) malloc(b_n);
    if (NULL == _b) {
        fprintf(stderr, "error: file_load: malloc %u\n", b_n);
        fclose(f_in);
        return NULL;
    }

    if (fread(_b, 1, b_n, f_in) < b_n) {
        fprintf(stderr, "error: file_load: fread only %u\n", b_n);
        fclose(f_in);
        return NULL;
    }

    fclose(f_in);
    return _b;
}

