#include "func.h"

// match order of funcs in func.h
const struct func_info _func_p_info [_4C_FUNC_P_ID_N + 1] = {
    {"print-i", 7,
        "_4c_func_print_i", 16,
        type_id_nil,
        1, {type_id_nil}, {type_id_int}},
    {"add-i", 5,
        "_4c_func_add_i", 14,
        type_id_int,
        2, {type_id_nil, type_id_nil}, {type_id_int, type_id_int}},
    {"set-i", 5,
        "_4c_func_set_i", 14,
        type_id_nil,
        2, {type_id_var, type_id_nil}, {type_id_int, type_id_int}},
    {"if", 2,
        "_4c_func_if", 11,
        type_id_nil,
        3, {type_id_nil, type_id_list, type_id_list}, {type_id_bool, type_id_nil, type_id_nil}},
    {NULL, 0, NULL, 0, type_id_nil, 0, {type_id_nil}, {type_id_nil}}
};

bool func_validate_args (struct func_info *_fi, struct syntax_tree *_st) {
    fprintf(stderr, "debug: func_validate_args\n");
    struct syntax_tree *_st2;

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
        fprintf(stderr, "error: func_validate_args: argument counts unequal in function %s\n",
                _fi->sym_s);
        return false;
    }

    // per arg types test
    for (uint32_t c = 0; c < _st->nodes_a.n; c++) {
        _st2 = array_get (&_st->nodes_a, c);
        if (NULL == _st2) {
            fprintf(stderr, "error: func_validate_args: array_get\n");
            return false;
        }

        // test type
        if ((type_id_nil != _fi->arg_type_ids[c]) &&\
                (_st2->ti.type_id != _fi->arg_type_ids[c])) {
            fprintf(stderr, "error: func_validate_args: type mismatch: arg %d: \"%s\" vs \"%s\" in func %s\n",
                    c + 1, type_id_syms[_st2->ti.type_id], type_id_syms[_fi->arg_type_ids[c]], _fi->sym_s);
            return false;
        }
        
        // if var type, and no subtype, assume var is new and needs function's required subtype (a hint for later)
        if ((type_id_var == _st2->ti.type_id) && 
                (type_id_nil == _st2->ti.subtype_id)) {
            _st2->ti.subtype_id = _fi->arg_subtype_ids[c];
            fprintf(stderr, "debug: func_validate_args: deduced new var \"%s\" has subtype %s\n",
                    _st2->ti.sym_s, type_id_syms[_st2->ti.subtype_id]);
        }

        // test subtype
        if (_st2->ti.subtype_id != _fi->arg_subtype_ids[c]) {
            fprintf(stderr, "error: func_validate_args: subtype mismatch: arg %d: \"%s\" vs \"%s\" in function %s\n",
                    c + 1, type_id_syms[_st2->ti.subtype_id], type_id_syms[_fi->arg_subtype_ids[c]], _fi->sym_s);
            return false;
        }
    }

    return true;
}

