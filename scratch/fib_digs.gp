/* c/o https://www.geeksforgeeks.org/finding-number-of-digits-in-nth-fibonacci-number/ */
default(realprecision, 16);

log10(n)=log(n)/log(10);

phi = (1 + sqrt(5)) / 2;
inv_log10_phi = 1 / log10(phi);
log10_5_d2_m1_t_inv_log10_phi = ((log10(5) / 2) - 1) * inv_log10_phi;

for(x=1,80, {
    n = ceil(x * inv_log10_phi + log10_5_d2_m1_t_inv_log10_phi);
    fib = fibonacci(n);
    print(n, " ", fib);
});

