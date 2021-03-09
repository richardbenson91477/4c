#include "func.h"

// match order of funcs in func.h
const struct func_info _func_p_info [_4C_FUNC_P_ID_N + 1] = {
    {"print", 5, "_4c_func_print", 14, type_id_nil, 1, {type_id_nil}},
    {"+", 1, "_4c_func_add", 10, type_id_int, 2, {type_id_int, type_id_int}},
    {"set", 3, "_4c_func_set", 12, type_id_var, 1, {type_id_nil}},
    {NULL, 0, NULL, 0, type_id_nil, 0, {type_id_nil}}
};

