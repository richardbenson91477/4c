#ifndef _4C_FUNC_H
#define _4C_FUNC_H

#include "type.h"
#include "syntax_tree.h"

#define _4C_FUNC_MAX_ARGS (32)

struct func_info {
    // function symbol
    char *sym_s;
    int32_t sym_n;
 
    // asm label
    char *label_s;
    int32_t label_n;

    // return type
    enum type_ids type_id_ret;

    // argument count
    int32_t arg_n;
    // argument types
    enum type_ids arg_type_ids[_4C_FUNC_MAX_ARGS];
    // argument subtypes
    enum type_ids arg_subtype_ids[_4C_FUNC_MAX_ARGS];
};

#define _4C_FUNC_P_ID_N (6)
enum func_p_ids {
    func_p_id_print_i = 0,
    func_p_id_add_i,
    func_p_id_set_i,
    func_p_id_if,
    func_p_id_do,
};

extern const struct func_info _func_p_info [_4C_FUNC_P_ID_N + 1];
extern bool func_validate_args (struct func_info *_fi, struct syntax_tree *_st);

#endif

