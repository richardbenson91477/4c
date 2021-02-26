#include "file.h"
#include "syntax_tree.h"

int main (int argc, const char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s source.4c\n", argv[0]);
        return -1;
    }

    uint8_t *_s = file_load (argv[1]);
    if (NULL == _s) {
        fprintf(stderr, "error: main: file_load\n");
        return -2;
    }

    uint8_t *_sa;

    struct syntax_tree *_syntax_root = syntax_tree_from_source (_s, &_sa);
    if (NULL == _syntax_root) {
        fprintf(stderr, "error: main: syntax_tree_from_source\n");
        return -3;
    }

    free(_s);

    if (0 == syntax_tree_destroy (_syntax_root)) {
        fprintf(stderr, "error: main: syntax_tree_destroy\n");
        return -4;
    }

    return 0;
}

