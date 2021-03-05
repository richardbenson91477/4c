#ifndef _4C_FUNC_H
#define _4C_FUNC_H

#include "type.h"

#define _4C_FUNC_MAX_ARGS (32)

struct func_info {
    // function symbol
    char *sym_s;
    uint32_t sym_n;
 
    // asm label
    char *label_s;
    uint32_t label_n;

    // return type
    enum type_ids type_id;

    // argument count
    uint32_t arg_n;

    // argument types
    enum type_ids arg_type_ids[_4C_FUNC_MAX_ARGS];
};

#define _4C_FUNC_P_ID_N (3)
enum func_p_ids {
    func_p_id_print = 0,
    func_p_id_add,
    func_p_id_set,
};

extern const struct func_info _func_p_info [_4C_FUNC_P_ID_N];

//extern bool type_ids_from_const_sym (struct type_info *_ti);

#endif

