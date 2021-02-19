#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define FNS_N (4)
typedef double (*FN_DBL_TO_DBL)(double);
double fn_1 (double x) {
    return x * x - 2.0;
}
double fn_2 (double x) {
    return log(x) - 1;
}
double fn_3 (double x) {
    return x * x - x - 1;
}
double fn_4 (double x) {
    return sin(x);
}
struct fn_list {
    const FN_DBL_TO_DBL fn;
    const double init_guess;
    const char name[32];
} fns[FNS_N] = {{fn_1, 1.0, "√2"}, 
                {fn_2, 1.0, "ℯ"},
                {fn_3, 1.0, "φ"},
                {fn_4, 3.0, "π"}};

double newton_root (FN_DBL_TO_DBL fn, const double init_guess, const double err_eps,
        const uint32_t max_steps, uint32_t *_steps) {
    double guess = init_guess;
    const double dt = 1e-6;
    uint32_t step_c;

    for (step_c = 0; step_c < max_steps; step_c ++) {
        double e = fn(guess);
        if (fabs(e) <= err_eps) {
            *_steps = step_c;
           return guess;
        }

        double d = (fn(guess + dt) - e) / dt;
        guess = guess - (e / d);
    }

    *_steps = -1;
    return guess;
}

int32_t main (void) {
    const double eps = 1e-14;
    const uint32_t max_steps = 50;
    uint32_t steps;

    for (uint32_t fns_c = 0; fns_c < FNS_N; fns_c ++) {
        struct fn_list *_fnl = &fns[fns_c];

        printf("%s:", _fnl->name);

        double r = newton_root(_fnl->fn, _fnl->init_guess, eps, max_steps, &steps);
        if (steps == (uint32_t)-1) {
            printf("(NOTE: reached max steps)");
        }
        printf("%.15f, %u steps\n", r, steps);
    
    }

    return 0;
}

