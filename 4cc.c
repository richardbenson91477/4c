#include "file.h"
#include "syntax_tree.h"

int main (int argc, const char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s source.4c\n", argv[0]);
        return -1;
    }

    uint8_t *_b = file_load (argv[1]);
    if (NULL == _b) {
        fprintf(stderr, "file_load failed\n");
        return -2;
    }

    struct syntax_tree *_syntax_root = syntax_tree_from_source (_b);
    if (NULL == _syntax_root) {
        fprintf(stderr, "syntax_tree_from_source failed\n");
        return -3;
    }

    free(_b);

    if (0 == syntax_tree_destroy (_syntax_root)) {
        fprintf(stderr, "syntax_tree_destroy failed\n");
        return -4;
    }

    return 0;
}

