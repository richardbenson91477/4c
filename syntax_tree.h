#ifndef _4C_SYNTAX_TREE_H
#define _4C_SYNTAX_TREE_H

#include "cstd.h"
#include "array.h"
#include "type.h"

enum elem_types {
    elem_type_funcall,
    elem_type_list,
    elem_type_const,
    elem_type_var,
};

struct syntax_tree {
    // NOTE: keep these items "calloc"-able
    enum elem_types elem_type;

    uint32_t id_n;
    uint8_t *id_s;

    enum type_ids type_id;
    union {
        struct type_func func;
        struct type_num num;
        struct type_num_array num_array;
        struct type_bool bool;
        struct type_string string;
        struct type_user user;
    } type;

    struct array nodes;
};

extern struct syntax_tree *syntax_tree_from_source (uint8_t *_s, uint8_t **__sa);
extern uint32_t syntax_tree_destroy (struct syntax_tree *_st);

#endif

