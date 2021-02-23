// nitro blaze lite
#ifndef _4C_LIST_H_
#define _4C_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define _4C_LIST_BLOCKSIZE (512)

struct list {
    void **__p;
    uint32_t n;

    uint32_t bn;
};

extern uint32_t list_add (struct list *_l, void *_v);
extern uint32_t list_del (struct list *_l, uint32_t i);

#endif

