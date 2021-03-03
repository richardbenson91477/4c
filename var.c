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

    // _ti_partial should contain sym_s, sym_n
    _vi->ti.sym_n = _ti_partial->sym_n;
    _vi->ti.sym_s = strdup(_ti_partial->sym_s);

    // create a label
    // TODO

    return _vi;
}

