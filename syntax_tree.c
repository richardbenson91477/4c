#include "syntax_tree.h"

uint8_t *syntax_tree_symbol_seek (uint8_t *_s) {
    printf("debug: syntax_tree_symbol_seek\n");

    uint8_t *_m;

    _m = _s;
    while ('\0' != *_m) {
        if (isspace(*_m)) {
            // ignore white-spaces
            _m += 1;
            continue;
        }
        else if (';' == *_m) {
            // comment line
            while ('\n' != *_m) {
                _m += 1;
                if ('\0' == *_m)
                    break;
            }
            printf("debug: syntax_tree_symbol_seek: skipped comment\n");
        }
        else {
            return _m;
        }
    }

    return NULL;
}

uint8_t *syntax_tree_symbol_read (uint8_t *_s, uint8_t **__sa) {
    printf("debug: syntax_tree_symbol_read\n");

    uint32_t s_n;
    uint8_t *_m;

    _m = _s;
    if (NULL == _m) {
        fprintf(stderr, "error: syntax_tree_symbol_read: NULL\n");
        return NULL;
    }
    else if ('\0' == *_m) {
        fprintf(stderr, "error: syntax_tree_symbol_read: NIL\n");
        return NULL;
    }
    
    s_n = 0;
    if ('\"' == *_m) {
        s_n += 1;
        _m += 1;
        // seek end of string consant
        while ('\0' != *_m) {
            if ('\"' == *_m)
                break;

            s_n += 1;
            _m += 1;
        }
        s_n += 1;
        _m += 1;
     }
    else {
        // seek end of symbol
        while ('\0' != *_m) {
            // symbol delimeters
            if ((isspace(*_m)) || (']' == *_m) || (')' == *_m))
                break;

            s_n += 1;
            _m += 1;
        }
    }

    if (0 == s_n) {
        fprintf(stderr, "error: syntax_tree_symbol_read: empty\n");
        return NULL;
    }

    uint8_t *id_s = malloc(s_n + 1);
    if (NULL == id_s) {
        fprintf(stderr, "error: syntax_tree_symbol_read: malloc\n");
        return NULL;
    }

    strncpy (id_s, _s, s_n);
    id_s[s_n] = '\0';

    *__sa = _m;
    return id_s;
};

struct syntax_tree *syntax_tree_new () {
    printf("debug: syntax_tree_new\n");

    struct syntax_tree *_st;

    _st = (struct syntax_tree *)calloc (1, sizeof(struct syntax_tree));
    if (NULL == _st) {
        fprintf(stderr, "error: syntax_tree_new: calloc\n");
        return NULL;
    }

    return _st;
}

struct syntax_tree *syntax_tree_from_source (uint8_t *_s, uint8_t **__sa) {
    printf("debug: syntax_tree_from_source\n");

    struct syntax_tree *_st, *_st2;
    uint8_t *_m, *_ma;

    if (NULL == _s) {
        fprintf(stderr, "error: syntax_tree_from_source: NULL\n");
        return NULL;
    }

    _st = syntax_tree_new();
    if (NULL == _st) {
        fprintf(stderr, "error: syntax_tree_from_source: syntax_tree_new\n");
        return NULL;
    }
 
    // seek ahead to something significant
    _m = syntax_tree_symbol_seek (_s);
    if (NULL == _m) {
        fprintf(stderr, "error: syntax_tree_from_source: NULL (2)\n");
        return NULL;
    }

    if ('(' == *_m) {
        printf("debug: syntax_tree_from_source: found function call\n");
        // function call
        _st->elem_type = elem_type_funcall;
    }
    else if ('[' == *_m) {
        printf("debug: syntax_tree_from_source: found list\n");
        // list
        _st->elem_type = elem_type_list;
    }
    // -, 0-9, ', " 
    else if (('\'' == *_m) || ('\"' == *_m) ||
            ('-' == *_m) || isdigit(*_m)) {
        printf("debug: syntax_tree_from_source: found constant\n");
        // constant
        _st->elem_type = elem_type_const;
    }
    else {
        printf("debug: syntax_tree_from_source: found variable\n");
        // variable
        _st->elem_type = elem_type_var;
    }

    // move just past '[' or '('
    if ((elem_type_funcall == _st->elem_type) ||
            (elem_type_list == _st->elem_type)) {
        _m += 1;
        if ('\0' == *_m) {
            fprintf(stderr, "error: syntax_tree_from_source: NIL (2)\n");
            return NULL;
        }

        if ((elem_type_funcall == _st->elem_type) &&
                (')' == *_m)) {
            fprintf(stderr, "error: syntax_tree_from_source: function name missing\n");
            return NULL;
        }
    }

    // read symbold id (unless this is a list)
    if (elem_type_list != _st->elem_type) {
        _st->id_s = syntax_tree_symbol_read (_m, &_ma);
        if (NULL == _st->id_s) {
            fprintf(stderr, "error: syntax_tree_from_source: syntax_tree_symbol_read\n");
            return NULL;
        }
        _st->id_n = _ma - _m;

        printf("debug: syntax_tree_from_source: found symbol \"%s\"\n", _st->id_s);
        _m = _ma;
    }

    // if this is a constant or variable work is done here
    if ((elem_type_const == _st->elem_type) ||
            (elem_type_var == _st->elem_type)) {
        *__sa = _m;
        return _st;
    }

    // otherwise recurse
    while ('\0' != *_m) {
        // seek ahead to something significant (again)
        _ma = syntax_tree_symbol_seek (_m);
        if (NULL == _ma) {
            fprintf(stderr, "error: syntax_tree_from_source: NULL (3)\n");
            return NULL;
        }
        _m = _ma;

        // end of function call or list
        if (((elem_type_funcall == _st->elem_type) &&
                (')' == *_m)) || 
            ((elem_type_list == _st->elem_type) &&
                (']' == *_m))) {
            if (elem_type_funcall == _st->elem_type) {
                printf("debug: syntax_tree_from_source: found function call end\n");
            }
            else {
                printf("debug: syntax_tree_from_source: found list end\n");
            }
            _m += 1;
            *__sa = _m;
            return _st;
        }

        _st2 = syntax_tree_from_source (_m, &_ma);
        if (NULL == _st) {
            fprintf(stderr, "error: syntax_tree_from_source: syntax_tree_from_source\n");
            return NULL;
        }
        _m = _ma;

        if (0 == array_add (&_st->nodes, _st2)) {
            fprintf(stderr, "error: syntax_tree_from_source: array_add\n");
            return NULL;
        }
    }

    *__sa = _m;
    return _st;
}

uint32_t syntax_tree_destroy (struct syntax_tree *_st) {
    printf("debug: syntax_tree_destroy\n");

    if (NULL == _st) {
        fprintf(stderr, "error: syntax_tree_destroy: NULL\n");
        return 0;
    }

    return 0;
}

