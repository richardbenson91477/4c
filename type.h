#ifndef _4C_TYPE_H
#define _4C_TYPE_H

#include "cstd.h"
#include "array.h"
#include "number.h"

enum type_ids {
    type_id_nil = 0,
    type_id_func,
    type_id_num,
    type_id_bool,
    type_id_string,
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

// NOTE: type_format_* structure data in memory during target program runtime, to be used by specialized linked-in runtime functions such as "number_to_d"

// NOTE: keep these type_format_* items "zero-able to init"

struct type_format_func {
    // return type detauls
    // argument list details
    // ...?
};

struct type_format_num {
    struct number n;
};

struct type_format_bool {
    uint8_t t_;
};

struct type_format_string {
    // putting this first might simplify conversion to C strings
    char *_s;
    uint32_t s_n;
};

struct type_format_list {
    struct array a;
};
 
struct type_format_user {
    // type_info array representing member items
    struct array items_a;
};
 
extern enum type_ids type_id_from_symbol (char *_s, uint32_t s_n);

#endif

