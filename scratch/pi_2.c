#include <stdio.h>
#include <stdint.h>
#include <math.h>

// for reference
const double pi_valid = 3.141592653589793238;

// a way to estimate π c/o https://www.youtube.com/watch?v=FQ1k_YpyG_A
int main () {
    const uint64_t num_steps = 1e+9;
    const double step = 1.0 / (double)num_steps;
    double x, total;

    total = 0.0;
    for (uint64_t i = 0; i < num_steps; i ++) {
        // 0.5 for "midpoint Riemann sum"
        x = (i + 0.5) * step; 
        total += 4.0 / (1.0 + x * x);
        //printf ("%.16f %.16f\n", x, total);
    }
    double pi = step * total;

    printf ("%.16f %.16f\n", pi, pi_valid);
    return 0;
}

