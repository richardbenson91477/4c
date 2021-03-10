#include "func.h"

// match order of funcs in func.h
const struct func_info _func_p_info [_4C_FUNC_P_ID_N + 1] = {
    {"print-i", 7, "_4c_func_print_i", 16, type_id_nil, 1, {type_id_nil}, {type_id_int}},
    {"add-i", 5, "_4c_func_add_i", 14, type_id_int, 2, {type_id_nil, type_id_nil}, {type_id_int, type_id_int}},
    {"set-i", 5, "_4c_func_set_i", 14, type_id_nil, 2, {type_id_var, type_id_nil}, {type_id_int, type_id_int}},
    {NULL, 0, NULL, 0, type_id_nil, 0, {type_id_nil}, {type_id_nil}}
};

bool func_validate_args (struct func_info *_fi, struct syntax_tree *_st) {
    fprintf(stderr, "debug: func_validate_args\n");
    struct syntax_tree *_st2;

    if (! _fi) {
        fprintf(stderr, "error: func_validate_args: NULL func_info\n");
        return false;
    }
    if (! _st) {
        fprintf(stderr, "error: func_validate_args: NULL syntax_tree\n");
        return false;
    }

    // argument count check
    if (_st->nodes_a.n != _fi->arg_n) {
        fprintf(stderr, "error: func_validate_args: argument counts unequal in function %s\n",
                _fi->sym_s);
        return false;
    }

    for (uint32_t c = 0; c < _st->nodes_a.n; c++) {
        _st2 = array_get (&_st->nodes_a, c);
        if (! _st2) {
            fprintf(stderr, "error: func_validate_args: array_get\n");
            return false;
        }

        // test type
        if ((type_id_nil != _fi->arg_type_ids[c]) &&\
                (_st2->ti.type_id != _fi->arg_type_ids[c])) {
            fprintf(stderr, "error: func_validate_args: type mismatch: \"%s\" vs \"%s\" in function %s\n",
                type_id_syms[_st2->ti.type_id], type_id_syms[_fi->arg_type_ids[c]], _fi->sym_s);
            return false;
        }

        // test subtype
        if (_st2->ti.subtype_id != _fi->arg_subtype_ids[c]) {
            fprintf(stderr, "error: func_validate_args: subtype mismatch: \"%s\" vs \"%s\" in function %s\n",
                type_id_syms[_st2->ti.subtype_id], type_id_syms[_fi->arg_subtype_ids[c]], _fi->sym_s);
            return false;
        }
    }

    return true;
}

