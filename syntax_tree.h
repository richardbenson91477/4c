#ifndef _4C_SYNTAX_TREE_H
#define _4C_SYNTAX_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct syntax_tree {
    
};

extern struct syntax_tree *syntax_tree_from_source (uint8_t *_b);
extern uint32_t syntax_tree_destroy (struct syntax_tree *_st);

#endif

