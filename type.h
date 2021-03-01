#ifndef _4C_TYPE_H
#define _4C_TYPE_H

#include "cstd.h"
#include "array.h"

enum type_ids {
    type_id_nil = 0,
    type_id_func,
    type_id_i32,
    type_id_s32,
    type_id_i64,
    type_id_s64,
    type_id_f32,
    type_id_f64,
    type_id_bool,
    type_id_str,
    type_id_list,
    type_id_user,
};

extern const char *type_id_names[];

// NOTE: keep these items "zero-able to init"
struct type_info {

    uint32_t name_n;
    char *name_s;

    enum type_ids type_id;
    
    // asm label or 0/NULL
    uint32_t label_n;
    char *label_s;
};

extern enum type_ids type_id_from_symbol (char *_s, uint32_t s_n);

#endif

