#include "func.h"

// match order of funcs in func.h
const struct func_info _func_p_info [_4C_FUNC_P_ID_N + 1] = {
    {"print-i", 7, func_p_id_print_i,
        "_4c_func_print_i", 16,
        type_id_nil,
        1, {type_id_nil},
           {type_id_int}},
    {"print-s", 7, func_p_id_print_s,
        "_4c_func_print_s", 16,
        type_id_nil,
        1, {type_id_nil},
           {type_id_str}},
    {"add-i", 5, func_p_id_add_i,
        "_4c_func_add_i", 14,
        type_id_int,
        2, {type_id_nil, type_id_nil},
           {type_id_int, type_id_int}},
    {"set-i", 5, func_p_id_set_i,
        "_4c_func_set_i", 14,
        type_id_nil,
        2, {type_id_var, type_id_nil},
           {type_id_int, type_id_int}},
    {"set-func", 8, func_p_id_set_func,
        "_4c_func_set_i", 17,
        type_id_nil,
        2, {type_id_var, type_id_nil},
           {type_id_func, type_id_func}},
    {"if", 2, func_p_id_if,
        "_4c_func_if", 11,
        type_id_nil,
        3, {type_id_nil, type_id_list, type_id_list},
           {type_id_bool, type_id_nil, type_id_nil}},
    {"do", 2, func_p_id_do,
        "_4c_func_do", 11,
        type_id_func,
        3, {type_id_list, type_id_type, type_id_list},
           {type_id_nil, type_id_nil, type_id_nil}},
    {"return-i", 8, func_p_id_return_i,
        "_4c_func_return_i", 17,
        type_id_int, // returns don't really return a value, but this is handy for type checking "do"
        1, {type_id_nil},
           {type_id_int}},
    {"return-b", 8, func_p_id_return_b,
        "_4c_func_return_b", 17,
        type_id_bool, // see above comment
        1, {type_id_nil},
           {type_id_bool}},
    {"neq-i", 5, func_p_id_neq_i,
        "_4c_func_neq_i", 14,
        type_id_bool,
        2, {type_id_nil, type_id_nil},
           {type_id_int, type_id_int}},
    {NULL, 0, 0, NULL, 0, type_id_nil, 0, {type_id_nil}, {type_id_nil}}
};

bool func_validate_args (struct func_info *_fi, struct syntax_tree *_st) {
    fprintf(stderr, "debug: func_validate_args\n");
    struct syntax_tree *_st2, *_st3, *_st4;
    struct type_info type_id_inner_ret;

    if (NULL == _fi) {
        fprintf(stderr, "error: func_validate_args: NULL func_info\n");
        return false;
    }
    if (NULL == _st) {
        fprintf(stderr, "error: func_validate_args: NULL syntax_tree\n");
        return false;
    }

    // argument count check
    if (_st->nodes_a.n != _fi->arg_n) {
        fprintf(stderr, "error: func_validate_args: argument counts unequal in function \"%s\"\n",
                _fi->sym_s);
        return false;
    }

    // per arg type test
    for (int32_t c = 0; c < _st->nodes_a.n; c++) {
        _st2 = array_get (&_st->nodes_a, c);
        if (NULL == _st2) {
            fprintf(stderr, "error: func_validate_args: array_get\n");
            return false;
        }

        // test type if specified
        if ((type_id_nil != _fi->arg_type_ids[c]) &&\
                (_st2->ti.type_id != _fi->arg_type_ids[c])) {
            fprintf(stderr, "error: func_validate_args: type mismatch: arg %d: \"%s\" vs \"%s\" "
                        "in function \"%s\"\n",
                    c + 1,
                    type_id_syms[_st2->ti.type_id], type_id_syms[_fi->arg_type_ids[c]],
                    _fi->sym_s);
            return false;
        }
        
        // var is new if type #:var, subtype #:nil
        if ((type_id_var == _st2->ti.type_id) && 
                (type_id_nil == _st2->ti.subtype_id)) {
            // set subtype hint using function's required subtype
            _st2->ti.subtype_id = _fi->arg_subtype_ids[c];
            fprintf(stderr, "debug: func_validate_args: deduced new var \"%s\" has subtype \"%s\"\n",
                    _st2->ti.sym_s, type_id_syms[_st2->ti.subtype_id]);
        }

        // test subtype if specified
        if ((type_id_nil != _fi->arg_subtype_ids[c]) &&\
                (_st2->ti.subtype_id != _fi->arg_subtype_ids[c])) {
            fprintf(stderr, "error: func_validate_args: subtype: arg %d: \"%s\" vs \"%s\" "
                    "in function \"%s\"\n",
                    c + 1,
                    type_id_syms[_st2->ti.subtype_id], type_id_syms[_fi->arg_subtype_ids[c]],
                    _fi->sym_s);
            return false;
        }
    }

    // function specific in-depth argument type tests
    if (func_p_id_print_i == _fi->func_p_id) {
    }
    else if (func_p_id_add_i == _fi->func_p_id) {
    }
    else if (func_p_id_set_i == _fi->func_p_id) {
    }
    else if (func_p_id_if == _fi->func_p_id) {
    }
    // "do" arguments
    else if (func_p_id_do == _fi->func_p_id) {
        // var list
        // format: [(var, type) * x] from x = 0 -> max
        _st2 = array_get (&_st->nodes_a, 0);
        if (NULL == _st2) {
            fprintf(stderr, "error: func_validate_args: array_get (2)\n");
            return false;
        }

        // var list item count must be an even number
        if (0 != (_st2->nodes_a.n % 2)) {
            fprintf(stderr, "error: func_validate_args: \"do\": odd var count\n");
            return false;
        }

        // var list per item type test
        for (int32_t c = 0; c < _st2->nodes_a.n; c += 2) {
            // get item
            _st3 = array_get (&_st2->nodes_a, c);
            if (NULL == _st3) {
                fprintf(stderr, "error: func_validate_args: array_get (3)\n");
                return false;
            }
            // ensure #:var
            if (type_id_var != _st3->ti.type_id) {
                fprintf(stderr, "error: func_validate_args: \"do\": arg 0 elem %d not #:var\n", c);
                return false;
            }
            
            // get next item
            _st4 = array_get (&_st2->nodes_a, c + 1);

            // ensure type #:type
            if (type_id_type != _st4->ti.type_id) {
                fprintf(stderr, "error: func_validate_args: \"do\": arg 0 elem %d not #:type\n", c + 1);
                return false;
            }
            
            // set var subtype hint
            _st3->ti.subtype_id = _st4->ti.subtype_id;

            fprintf(stderr, "debug: func_validate_args: \"do\": set var \"%s\" subtype \"%s\"\n",
                    _st3->ti.sym_s, type_id_syms[_st4->ti.subtype_id]);
        }

        // function list
        _st2 = array_get (&_st->nodes_a, 2);
        if (NULL == _st2) {
            fprintf(stderr, "error: func_validate_args: array_get (4)\n");
            return false;
        }
            
        // get the inner return type
        _st3 = array_get (&_st->nodes_a, 1);
        if (NULL == _st3) {
            fprintf(stderr, "error: func_validate_args: array_get (5)\n");
            return false;
        }

        // validate that inner return- call types match current return type
        if (! func_validate_return_type (_st2, _st3->ti.subtype_id)) {
            fprintf(stderr, "error: func_validate_args: func_validate_return_type\n");
            return false;
        }
    }

    return true;
}

// search syntax subtrees, ignoring nested "do"s, to validate return- call types
bool func_validate_return_type (struct syntax_tree *_st, enum type_ids type_id_ret) {
    fprintf(stderr, "debug: func_validate_return_type\n");
    struct syntax_tree *_st2;
    struct func_info *_fi;

    if (NULL == _st) {
        fprintf(stderr, "error: func_validate_return_type: NULL syntax_tree\n");
        return false;
    }

    // are we a predefined function
    _fi = _st->ti._fi;
    if (NULL != _fi) {
        // which one
        switch (_fi->func_p_id) {
            case func_p_id_do:
                fprintf(stderr, "debug: func_validate_return_type: ignoring inner do\n");
                // do not recurse inner "do"
                return true;
                break;

            case func_p_id_return_i:
            case func_p_id_return_b:
                if (_fi->type_id_ret != _fi->type_id_ret) {
                    fprintf(stderr, "error: func_validate_return_type: incorrect return type %s: "
                            "expected %s\n",
                            type_id_syms[_fi->type_id_ret], type_id_syms[_fi->type_id_ret]);
                    return false;
                }
                else {
                    fprintf(stderr, "debug: func_validate_return_type: correct return type\n");
                    return true;
                }
                break;
        }
    }

    // skip other unsuitable branches
    // ...?

    // recurse into any remaining branches
    for (int32_t c = 0; c < _st->nodes_a.n; c++) {
        _st2 = array_get (&_st->nodes_a, c);
        if (NULL == _st2) {
            fprintf(stderr, "error: func_validate_return_type: array_get\n");
            return false;
        }

        if (! func_validate_return_type (_st2, type_id_ret)) {
            fprintf(stderr, "error: func_validate_return_type: func_validate_return_type\n");
            return false;
        }
    }

    return true;
}

