#ifndef _4C_ARRAY_H_
#define _4C_ARRAY_H_

#include "cstd.h"

#define _4C_ARRAY_BLOCKSIZE (512)

// NOTE: keep these items "zero-able to init"
struct array {
    void **__p;
    int32_t n;
    int32_t b_n;
};

extern bool array_add (struct array *_a, void *_v);
extern bool array_del (struct array *_a, int32_t i);
extern void *array_get (struct array *_a, int32_t i);

#endif

