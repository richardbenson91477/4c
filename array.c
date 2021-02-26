#include "array.h"

uint32_t array_add (struct array *_a, void *_v) {
    printf("debug: array_add\n");

    if (_a->n == (_4C_ARRAY_BLOCKSIZE * _a->bn)) {
        _a->bn ++;

        void **__v = (void **) realloc(_a->__p, 
            (_4C_ARRAY_BLOCKSIZE * _a->bn) * sizeof(void *));

        if (NULL == __v) {
            fprintf(stderr, "error: array_add: realloc\n");
            return 0;
        }

        _a->__p = __v;
    }

    *(_a->__p + _a->n) = _v;

    _a->n ++;
    return 1;
}

uint32_t array_del (struct array *_a, uint32_t i) {
    printf("debug: array_del\n");

    if ((0 == _a->n) || (i >= _a->n)) {
        fprintf(stderr, "error: array_del: empty\n");
        return 0;
    }

    void **__v = _a->__p + i;
    for (uint32_t c = i; c < (_a->n - 1); c ++) {
        *__v = *(__v + 1);
        __v ++;
    }

    _a->n --;
    return 1;
}
