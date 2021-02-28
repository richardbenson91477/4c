#include "number.h"

struct number *number_from_s (char *_s) {
    printf("debug: number_from_s %s\n", _s);

    // TODO: construct and return a number

    return NULL;
}
// NOTE: linked to target code

double number_to_d (struct number *_n) {
    //printf("debug: number_to_d);
 
    if (NULL == _n) {
        printf("error: number_to_d\n");
        return -0.0;
    }

    return _n->d;
}
// NOTE: linked to target code

