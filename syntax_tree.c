#include "syntax_tree.h"
#include <ctype.h>
#include <string.h>

char *syntax_tree_symbol_read (char *_s) {
    printf("debug: syntax_tree_symbol_read\n");

    uint32_t s_n;
    char *_m;

    _m = _s;
    if ((NULL == _m) || ('\0' == *_m)) {
        fprintf(stderr, "error: syntax_tree_symbol_read: NULL");
        return NULL;
    }

    s_n = 0;
    while ('\0' != *_m) {
        if ((isspace(*_m)) || (']' == *_m) || (')' == *_m))
            break;

        s_n += 1;
        _m += 1;
    }

    if (0 == s_n) {
        fprintf(stderr, "error: syntax_tree_symbol_read: NULL");
        return NULL;
    }

    char *_id = malloc(s_n + 1);
    if (NULL == _id) {
        fprintf(stderr, "error: syntax_tree_symbol_read: NULL");
        return NULL;
    }

    strncpy (_id, _s, s_n);
    _id[s_n] = '\0';

    return _id;
};

struct syntax_tree *syntax_tree_new () {
    printf("debug: syntax_tree_new\n");

    struct syntax_tree *_st;

    _st = (struct syntax_tree *)calloc (1, sizeof(struct syntax_tree));
    if (NULL == _st) {
        fprintf(stderr, "error: syntax_tree_new: calloc");
        return NULL;
    }

    return _st;
}

struct syntax_tree *syntax_tree_from_source (uint8_t *_b) {
    printf("debug: syntax_tree_from_source\n");

    struct syntax_tree *_st;
    uint8_t *_m, *_m2;

    if ((NULL == _b) || ('\0' == *_b)) {
        fprintf(stderr, "error: syntax_tree_from_source: NULL");
        return NULL;
    }

    _st = syntax_tree_new();
    if (NULL == _st) {
        fprintf(stderr, "error: syntax_tree_from_source: NULL");
        return NULL;
    }
    
    _m = _b;
    while ('\0' != *_m) {
        if (isspace(*_m)) {
            // ignore white-spaces
            _m += 1;
            continue;
        }
        if (';' == *_m) {
            // comment line
            while ('\n' != *_m) {
                _m ++;
                if ('\0' == *_m)
                    break;

            }
            printf ("skipped comment\n");
        }
        if ('(' == *_m) {
            // function call
            _st->elem_type = elem_type_func;

            _m += 1;
            if ('\0' == *_m) {
                fprintf(stderr, "error: syntax_tree_from_source: NULL");
                return NULL;
            }

            _st->_id = syntax_tree_symbol_read (_m);
            if (NULL == _st->_id) {
                fprintf(stderr, "error: syntax_tree_from_source: NULL");
                return NULL;
            }
 
            printf("found function \"%s\"\n", _st->_id);

            _m += strlen(_st->_id);
        }
        else if ('[' == *_m) {
            // list
            
            _m += 1;
        }
        // -, 0-9, ', " 
        else if (('\'' == *_m) || ('\"' == *_m) ||
                ('-' == *_m) || isdigit(*_m)) {
            // constant

            _m += 1;
        }
        else {
            // variable
            _m += 1;
        }
    }

    return _st;
}

uint32_t syntax_tree_destroy (struct syntax_tree *_st) {
    printf("debug: syntax_tree_destroy\n");

    if (NULL == _st) {
        fprintf(stderr, "error: syntax_tree_destroy: NULL");
        return 0;
    }

    return 0;
}

