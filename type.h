#ifndef _4C_TYPE_H
#define _4C_TYPE_H

#include "cstd.h"
#include "array.h"

#define _4C_TYPE_ID_N (10)
enum type_ids {
    type_id_nil = 0,
    type_id_func,
    type_id_int,
    type_id_float,
    type_id_bool,
    type_id_str,
    type_id_list,
    type_id_pconst,
    type_id_ptype,
    type_id_utype,
};

extern const char *type_id_syms[_4C_TYPE_ID_N];

// NOTE: keep these items "zero-able to init"
struct type_info {
    uint32_t sym_n;
    char *sym_s;
    
    enum type_ids type_id;
    enum type_ids subtype_id;

    // asm label or 0/NULL
    uint32_t label_n;
    char *label_s;
};

extern bool type_ids_from_const_sym (struct type_info *_ti);

#endif

