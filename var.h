#ifndef _4C_VAR_H
#define _4C_VAR_H

#include "cstd.h"
#include "type.h"

struct var {
    uint32_t name_n;
    char *name_s;

    uint32_t label_n;
    char *label_s;

    struct type_data td;
};

#endif

