#ifndef _4C_TYPE_H
#define _4C_TYPE_H

#include "cstd.h"
#include "array.h"
#include "number.h"

enum type_ids {
    type_id_func,
    type_id_num,
    type_id_num_array,
    type_id_bool,
    type_id_string,
    type_id_user,
};

extern const char *type_id_names[];

struct type_func {
    uint32_t label_n;
    char *label_s;

    // argument list details
    // ...
};

struct type_num {
    struct number n;
};

struct type_num_array {
    struct array n_array;
};
 
struct type_bool {
    uint8_t t_;
};

struct type_string {
    uint32_t s_n;
    char *_s;
};

struct type_user {
    struct array items;
};

#endif

