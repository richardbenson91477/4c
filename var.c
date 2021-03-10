#include "var.h"

struct var_info *var_info_from (struct type_info *_ti) {
    fprintf(stderr, "debug: var_info_from");

    struct var_info *_vi;

    // calloc to init new var
    _vi = (struct var_info *)calloc (1, sizeof(struct var_info));
    if (NULL == _vi) {
        fprintf(stderr, "error: var_info_from: calloc\n");
        return NULL;
    }

    // _ti must contain sym_s, sym_n
    _vi->ti.sym_s = strdup(_ti->sym_s);
    _vi->ti.sym_n = _ti->sym_n;

    // create a label
    // TODO

    return _vi;
}
