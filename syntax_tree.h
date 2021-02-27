#ifndef _4C_SYNTAX_TREE_H
#define _4C_SYNTAX_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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
    uint8_t *_id;
    struct array nodes;
};

extern struct syntax_tree *syntax_tree_from_source (uint8_t *_s, uint8_t **__sa);
extern uint32_t syntax_tree_destroy (struct syntax_tree *_st);

#endif

