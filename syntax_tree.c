#include "syntax_tree.h"
#include <ctype.h>

struct syntax_tree *syntax_tree_new () {
    struct syntax_tree *_st;

    _st = (struct syntax_tree *)calloc (1, sizeof(struct syntax_tree));
    if (! _st) {
        fprintf(stderr, "calloc failed\n");
        return NULL;
    }

    return _st;
}

struct syntax_tree *syntax_tree_from_source (uint8_t *_b) {
    struct syntax_tree *_st;
    uint8_t *_m, *_m2;

    if ((! _b) || (! *_b))
        return NULL;

    _st = syntax_tree_new();
    if (! _st)
        return NULL;
    
    _m = _b;
    while (*_m) {
        if (isspace(*_m)) {
            // ignore white-spaces
        }
        if (*_m == '(') {
            // function call

        }
        else if (*_m == '[') {
            // list
        }
        // -, 0-9, ', " 
        else if ((*_m == '\'') || (*_m == '\"') ||
                (*_m == '-') || isdigit(*_m)) {
            // constant
        }
        else {
            // variable

        }

        _m += 1;
    }

    return _st;
}

uint32_t syntax_tree_destroy (struct syntax_tree *_st) {
    if (! _st)
        return 0;

    return 0;
}

