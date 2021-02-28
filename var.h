#ifndef _4C_VAR_H
#define _4C_VAR_H

#include "cstd.h"
#include "type.h"

struct var_info {
    struct type_info ti;

    // TODO: whatever else vars crave below
};

extern struct var_info *var_info_from (struct type_info *_ti_partial);

#endif

