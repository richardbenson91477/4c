#include "syntax_tree.h"

uint8_t *syntax_tree_symbol_seek (char *_s) {
    printf("debug: syntax_tree_symbol_seek\n");

    char *_m;

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

uint32_t syntax_tree_symbol_len (char *_s) {
    printf("debug: syntax_tree_symbol_len\n");

    uint32_t s_n;
    char *_m;

    _m = _s;
    if (NULL == _m) {
        fprintf(stderr, "error: syntax_tree_symbol_len: NULL\n");
        return 0;
    }
    else if ('\0' == *_m) {
        fprintf(stderr, "error: syntax_tree_symbol_len: NIL\n");
        return 0;
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

    return s_n;
};

struct syntax_tree *syntax_tree_new () {
    printf("debug: syntax_tree_new\n");

    struct syntax_tree *_st;

    // calloc to init new syntax_tree
    _st = (struct syntax_tree *)calloc (1, sizeof(struct syntax_tree));
    if (NULL == _st) {
        fprintf(stderr, "error: syntax_tree_new: calloc\n");
        return NULL;
    }

    return _st;
}

struct syntax_tree *syntax_tree_from_source (char *_s, char **__sa) {
    printf("debug: syntax_tree_from_source\n");

    struct syntax_tree *_st, *_st2;
    char *_m, *_ma;

    if (NULL == _s) {
        fprintf(stderr, "error: syntax_tree_from_source: NULL\n");
        return NULL;
    }

    _st = syntax_tree_new ();
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

    // function call
    if ('(' == *_m) {
        printf("debug: syntax_tree_from_source: found function call\n");
        _st->syntax_type = syntax_funcall;
    }
    // list
    else if ('[' == *_m) {
        printf("debug: syntax_tree_from_source: found list\n");
        _st->syntax_type = syntax_list;
    }
    // constant
    else if (('\'' == *_m) || ('\"' == *_m) ||
            ('-' == *_m) || isdigit(*_m)) {
        printf("debug: syntax_tree_from_source: found constant\n");
        _st->syntax_type = syntax_const;
    }
    // variable
    else {
        printf("debug: syntax_tree_from_source: found variable\n");
        _st->syntax_type = syntax_var;
    }

    // move just past '[' or '('
    if ((syntax_funcall == _st->syntax_type) ||
            (syntax_list == _st->syntax_type)) {
        _m += 1;
        if ('\0' == *_m) {
            fprintf(stderr, "error: syntax_tree_from_source: NIL (2)\n");
            return NULL;
        }

        // disallow empty functions
        if ((syntax_funcall == _st->syntax_type) &&
                (')' == *_m)) {
            fprintf(stderr, "error: syntax_tree_from_source: function name missing\n");
            return NULL;
        }
    }

    // read symbol name (excepting list) into (type_info) ti
    if (syntax_list != _st->syntax_type) {
        uint32_t n = syntax_tree_symbol_len (_m);
        if (0 == n) {
            fprintf(stderr, "error: syntax_tree_from_source: syntax_tree_symbol_len\n");
            return NULL;
        }

        _st->ti.name_s = strndup(_m, n);
        _st->ti.name_n = n;

        _m += n;

        printf("debug: syntax_tree_from_source: found symbol \"%s\"\n", _st->ti.name_s);           
    }

    if ((syntax_const == _st->syntax_type) ||
            (syntax_var == _st->syntax_type)) {

        // deduce type_id from symbol
        _st->ti.type_id = type_id_from_symbol (_st->ti.name_s, _st->ti.name_n);

        printf("debug: syntax_tree_from_source: deduced type \"%s\"\n",
                type_id_names[_st->ti.type_id]);

        // save current position and return
        *__sa = _m;
        return _st;
    }
    else if (syntax_funcall == _st->syntax_type) {
        // first symbol in function call must be ':function type
        _st->ti.type_id = type_id_func;
    }

    while ('\0' != *_m) {
        // seek ahead to something significant (2)
        _ma = syntax_tree_symbol_seek (_m);
        if (NULL == _ma) {
            fprintf(stderr, "error: syntax_tree_from_source: NULL (3)\n");
            return NULL;
        }
        _m = _ma;

        // end of function call or list
        if (((syntax_funcall == _st->syntax_type) &&
                (')' == *_m)) || 
            ((syntax_list == _st->syntax_type) &&
                (']' == *_m))) {

            if (syntax_funcall == _st->syntax_type) {
                printf("debug: syntax_tree_from_source: found function call end\n");
            }
            else {
                printf("debug: syntax_tree_from_source: found list end\n");
            }

            // save current position and return
            _m += 1;
            *__sa = _m;
            return _st;
        }

        // recurse
        _st2 = syntax_tree_from_source (_m, &_ma);
        if (NULL == _st) {
            fprintf(stderr, "error: syntax_tree_from_source: syntax_tree_from_source\n");
            return NULL;
        }
        _m = _ma;

        // add resultant tree to nodes_a
        if (0 == array_add (&_st->nodes_a, _st2)) {
            fprintf(stderr, "error: syntax_tree_from_source: array_add\n");
            return NULL;
        }
    }

    // save current position and return
    *__sa = _m;
    return _st;
}

uint32_t syntax_tree_destroy (struct syntax_tree *_st) {
    printf("debug: syntax_tree_destroy\n");

    if (NULL == _st) {
        fprintf(stderr, "error: syntax_tree_destroy: NULL\n");
        return 0;
    }

    // TODO: actually decompose the tree

    return 0;
}

