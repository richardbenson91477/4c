#ifndef _4C_ARRAY_H_
#define _4C_ARRAY_H_

#include "cstd.h"

#define _4C_ARRAY_BLOCKSIZE (512)

// NOTE: keep these items "zero-able to init"
struct array {
    void **__p;
    uint32_t n;
    uint32_t b_n;
};

extern bool array_add (struct array *_a, void *_v);
extern bool array_del (struct array *_a, uint32_t i);

#endif

