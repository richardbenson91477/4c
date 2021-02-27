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

// NOTE: keep these items "zero-able to init"
struct syntax_tree {
    enum elem_types elem_type;

    uint32_t id_n;
    char *id_s;

    struct type_data td;

    struct array nodes_a;
};

extern struct syntax_tree *syntax_tree_from_source (char *_s, char **__sa);
extern uint32_t syntax_tree_destroy (struct syntax_tree *_st);

#endif

