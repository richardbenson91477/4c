#ifndef _4C_VAR_H
#define _4C_VAR_H

#include "cstd.h"
#include "type.h"

struct var {
    struct type_data td;

    // TODO: whatever else vars crave below
};

extern struct var *var_from_s (char *_s);

#endif

