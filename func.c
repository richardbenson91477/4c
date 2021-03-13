#include "func.h"

// match order of funcs in func.h
const struct func_info _func_p_info [_4C_FUNC_P_ID_N + 1] = {
    {"print-i", 7, func_p_id_print_i,
        "_4c_func_print_i", 16,
        type_id_nil,
        1, {type_id_nil},
           {type_id_int}},
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
        type_id_nil,
        1, {type_id_nil},
           {type_id_int}},
    {NULL, 0, 0, NULL, 0, type_id_nil, 0, {type_id_nil}, {type_id_nil}}
};

bool func_validate_args (struct func_info *_fi, struct syntax_tree *_st) {
    fprintf(stderr, "debug: func_validate_args\n");
    struct syntax_tree *_st2, *_st3, *_st4;

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

    // function specific in depth type tests
    if (func_p_id_print_i == _fi->func_p_id) {
    }
    else if (func_p_id_add_i == _fi->func_p_id) {
    }
    else if (func_p_id_set_i == _fi->func_p_id) {
    }
    else if (func_p_id_if == _fi->func_p_id) {
    }
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
    }

    return true;
}

