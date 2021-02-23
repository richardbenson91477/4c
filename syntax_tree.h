#ifndef _4C_SYNTAX_TREE_H
#define _4C_SYNTAX_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

enum elem_types {
    func,
    constant,
    list,
    var,
};

struct syntax_tree {
    elem_types elem_type;

    char *id;

    struct list *_branches;
};

extern struct syntax_tree *syntax_tree_from_source (uint8_t *_b);
extern uint32_t syntax_tree_destroy (struct syntax_tree *_st);

#endif

