#ifndef _4C_TYPE_H
#define _4C_TYPE_H

#include "cstd.h"
#include "array.h"

enum type_ids {
    type_id_nil = 0,
    type_id_func,
    type_id_int,
    type_id_float,
    type_id_bool,
    type_id_str,
    type_id_list,
//    type_id_type,
    type_id_user,
};

extern const char *type_id_syms[];

// NOTE: keep these items "zero-able to init"
struct type_info {
    uint32_t sym_n;
    char *sym_s;
    
    enum type_ids type_id;

    // asm label or 0/NULL
    uint32_t label_n;
    char *label_s;
};

extern enum type_ids type_id_from_const_sym (char *_s, uint32_t s_n);

#endif

