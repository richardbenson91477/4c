#ifndef _4C_NUMBER_H
#define _4C_NUMBER_H

#include "cstd.h"

// NOTE: keep these items "zero-able to init"
struct number {
    // cached as-needed standard type conversions for inter-op
    double d;
    float f;
    uint64_t u64;
    int64_t s64;
    uint32_t u32;
    int32_t s32;
    uint8_t u8;
    int8_t s8;

    // TODO: more complex mother type below
};

extern struct number *number_from_s (char *_s);

extern double number_to_d (struct number *_n);

#endif

