#ifndef _4C_SYNTAX_TREE_H
#define _4C_SYNTAX_TREE_H

#include "cstd.h"
#include "array.h"
#include "type.h"

enum syntax_types {
    syntax_funcall,
    syntax_list,
    syntax_const,
    syntax_var,
};

// NOTE: keep these items "zero-able to init"
struct syntax_tree {
    enum syntax_types syntax_type;

    struct type_data td;

    struct array nodes_a;
};

extern struct syntax_tree *syntax_tree_from_source (char *_s, char **__sa);
extern uint32_t syntax_tree_destroy (struct syntax_tree *_st);

#endif

