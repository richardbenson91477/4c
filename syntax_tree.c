#include "syntax_tree.h"

char *syntax_tree_sym_seek (char *_s) {
    fprintf(stderr, "debug: syntax_tree_sym_seek\n");

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
            fprintf(stderr, "debug: syntax_tree_sym_seek: skipped comment\n");
        }
        else {
            return _m;
        }
    }

    return NULL;
}

uint32_t syntax_tree_sym_len (char *_s) {
    fprintf(stderr, "debug: syntax_tree_sym_len\n");

    char *_m = _s;

    if (NULL == _m) {
        fprintf(stderr, "error: syntax_tree_sym_len: NULL\n");
        return 0;
    }
    else if ('\0' == *_m) {
        fprintf(stderr, "error: syntax_tree_sym_len: NIL\n");
        return 0;
    }
 
    // we have at least one character
    uint32_t s_n = 1;

    // is it a double-quote
    if ('\"' == *_m) {
        // seek end of string consant
        _m += 1;
        while ('\0' != *_m) {
            if ('\"' == *_m)
                break;

            s_n += 1;
            _m += 1;
        }
        if ('\"' == *_m) {
            s_n += 1;
            _m += 1;
        }
        else {
            // hit end of data
            // ...
        }
    }
    else {
        // seek end of symbol
        _m += 1;
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
    fprintf(stderr, "debug: syntax_tree_new\n");

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
    fprintf(stderr, "debug: syntax_tree_from_source\n");

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
    _m = syntax_tree_sym_seek (_s);
    if (NULL == _m) {
        fprintf(stderr, "error: syntax_tree_from_source: NULL (2)\n");
        return NULL;
    }

    // function call
    if ('(' == *_m) {
        fprintf(stderr, "debug: syntax_tree_from_source: found function call\n");
        _st->syntax_type = syntax_funcall;
    }
    // misplaced function call end
    else if (')' == *_m) {
        fprintf(stderr, "error: misplaced ')'\n");
        return NULL;
    }
    // list
    else if ('[' == *_m) {
        fprintf(stderr, "debug: syntax_tree_from_source: found list\n");
        _st->syntax_type = syntax_list;
    }
    // misplaced list end
    else if (']' == *_m) {
        fprintf(stderr, "error: misplaced ']'\n");
        return NULL;
    }
    // constant
    else if (('\'' == *_m) ||
            ('\"' == *_m) ||
            ('#' == *_m) ||
            ('-' == *_m) ||
            (':' == *_m) ||
            isdigit(*_m)) {
        fprintf(stderr, "debug: syntax_tree_from_source: found constant\n");
        _st->syntax_type = syntax_const;
    }
    // variable
    // TODO: enforce variable name rules
    else {
        fprintf(stderr, "debug: syntax_tree_from_source: found variable\n");
        _st->syntax_type = syntax_var;
    }

    // move one char past '[' or '('
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

    // read symbol (excepting list) into (type_info) ti
    if (syntax_list != _st->syntax_type) {
        uint32_t n = syntax_tree_sym_len (_m);
        if (0 == n) {
            fprintf(stderr, "error: syntax_tree_from_source: syntax_tree_sym_len\n");
            return NULL;
        }

        _st->ti.sym_s = strndup(_m, n);
        _st->ti.sym_n = n;

        _m += n;

        fprintf(stderr, "debug: syntax_tree_from_source: found symbol \"%s\"\n", _st->ti.sym_s);
    }

    if (syntax_const == _st->syntax_type) {
        // attempt to deduce type_id from const symbol
        if (false == type_ids_from_const_sym (&(_st->ti))) {
            fprintf(stderr, "error: syntax_tree_from_source: type_ids_from_const_sym\n");
            return NULL;
        }

        fprintf(stderr, "debug: syntax_tree_from_source: deduced type \"%s\"\n", type_id_syms[_st->ti.type_id]);

        // save current position and return
        *__sa = _m;
        return _st;
    }
    else if (syntax_var == _st->syntax_type) {
        _st->ti.type_id = type_id_var;

        // save current position and return
        *__sa = _m;
        return _st;
    }
    else if (syntax_funcall == _st->syntax_type) {
        // first symbol in function call deduced to be of ':function type
        _st->ti.type_id = type_id_func;
    }

    while ('\0' != *_m) {
        // seek ahead to something significant (2)
        _ma = syntax_tree_sym_seek (_m);
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
                fprintf(stderr, "debug: syntax_tree_from_source: found function call end\n");
            }
            else {
                fprintf(stderr, "debug: syntax_tree_from_source: found list end\n");
            }

            // save current position and return
            _m += 1;
            *__sa = _m;
            return _st;
        }

        // recurse
        _st2 = syntax_tree_from_source (_m, &_ma);
        if (NULL == _st2) {
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

bool syntax_tree_destroy (struct syntax_tree *_st) {
    fprintf(stderr, "debug: syntax_tree_destroy\n");

    if (NULL == _st) {
        fprintf(stderr, "error: syntax_tree_destroy: NULL\n");
        return false;
    }

    // TODO: actually decompose the tree

    return true;
}

