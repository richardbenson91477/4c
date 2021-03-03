#include "array.h"

bool array_add (struct array *_a, void *_v) {
    fprintf(stderr, "debug: array_add\n");

    if (_a->n == (_4C_ARRAY_BLOCKSIZE * _a->b_n)) {
        _a->b_n ++;

        void **__v = (void **) realloc(_a->__p, 
            (_4C_ARRAY_BLOCKSIZE * _a->b_n) * sizeof(void *));

        if (NULL == __v) {
            fprintf(stderr, "error: array_add: realloc\n");
            return false;
        }

        _a->__p = __v;
    }

    *(_a->__p + _a->n) = _v;

    _a->n ++;
    return true;
}

bool array_del (struct array *_a, uint32_t i) {
    fprintf(stderr, "debug: array_del\n");

    if ((0 == _a->n) || (i >= _a->n)) {
        fprintf(stderr, "error: array_del: empty\n");
        return false;
    }

    void **__v = _a->__p + i;
    for (uint32_t c = i; c < (_a->n - 1); c ++) {
        *__v = *(__v + 1);
        __v ++;
    }

    _a->n --;
    return true;
}

