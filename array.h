#ifndef _4C_ARRAY_H_
#define _4C_ARRAY_H_

#include "cstd.h"

#define _4C_ARRAY_BLOCKSIZE (512)

struct array {
    // NOTE: keep these items "calloc"-able
    void **__p;
    uint32_t n;
    uint32_t b_n;
};

extern uint32_t array_add (struct array *_a, void *_v);
extern uint32_t array_del (struct array *_a, uint32_t i);

#endif

