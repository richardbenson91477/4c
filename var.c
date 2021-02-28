#include "var.h"

struct var_info *var_info_from (struct type_info *_ti_partial) {
    printf("debug: var_from");

    struct var_info *_vi;

    // calloc to init new var
    _vi = (struct var_info *)calloc (1, sizeof(struct var_info));
    if (NULL == _vi) {
        fprintf(stderr, "error: var_from: calloc\n");
        return NULL;
    }

    // _ti_partial should contain name_s, name_n and type_id
    _vi->ti.name_n = _ti_partial->name_n;
    _vi->ti.name_s = strdup(_ti_partial->name_s);
    _vi->ti.type_id = _ti_partial->type_id;

    // create a label
    // TODO

    return _vi;
}

