#include "list.h"

uint32_t list_add (struct list *_l, void *_v) {
    if (_l->n == (_4C_LIST_BLOCKSIZE * _l->bn)) {
        _l->bn ++;

        void **__v = (void **) realloc(_l->__p, 
            (_4C_LIST_BLOCKSIZE * _l->bn) * sizeof(void *));

        if (! __v)
            return 0;

        _l->__p = __v;
    }

    *(_l->__p + _l->n) = _v;

    _l->n ++;
    return 1;
}

uint32_t list_del (struct list *_l, uint32_t i) {
    if ((! _l->n) || (i >= _l->n))
        return 0;

    void **__v = _l->__p + i;
    for (uint32_t c = i; c < (_l->n -1); c ++) {
        *__v = *(__v + 1);
        __v ++;
    }

    _l->n --;
    return 1;
}

