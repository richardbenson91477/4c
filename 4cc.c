#include "file.h"

int main (int argc, const char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s source.4c\n", argv[0]);
        return -1;
    }

    uint8_t *_b = file_load (argv[1]);
    if (! _b) {
        fprintf(stderr, "file_load failed\n");
        return -2;
    }

    free(_b);

    return 0;
}

