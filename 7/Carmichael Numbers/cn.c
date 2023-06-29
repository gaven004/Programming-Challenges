/*
 * Carmichael Numbers
 * PC/UVa IDs: 110702/10006
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAXN 65000

unsigned int n_prime_numbers;
unsigned int P[MAXN];

int is_prime_number(unsigned int n) {
    unsigned int i, s;

    if (n <= 3) {
        return 1;
    }

    s = sqrt(n) + 1; // 由于精度问题，保险起见加1

    for (i = 1; P[i] <= s && i < n_prime_numbers; ++i) {
        if (n % P[i] == 0) {
            return 0;
        }
    }

    return 1;
}

void init_prime_number_table() {
    unsigned int i;

    P[0] = 2;
    n_prime_numbers = 1;

    for (i = 3; i <= MAXN; i += 2) {
        if (is_prime_number(i)) {
            P[n_prime_numbers] = i;
            n_prime_numbers++;
        }
    }
}

int cmp(const void *a, const void *b) {
    return (*(int *) a - *(int *) b);
}

int is_composite_number(unsigned int n) {
    return bsearch(&n, P, n_prime_numbers, sizeof(unsigned int), cmp) == NULL;
}

/* get a ^ x mod n */
unsigned int mod(unsigned int a, unsigned int x, unsigned int n) {
    unsigned int result = 1;

    while (x > 0) {
        if (x & 1) {
            result = (result * a) % n;
        }
        a = (a * a) % n;
        x >>= 1;
    }

    return result;
}

int is_carmichael_number(unsigned int n) {
    int i;
    unsigned int s;

    if (!is_composite_number(n)) {
        return 0;
    }

    /* 必然为奇数 */
    if (!(n & 1)) {
        return 0;
    }

    /* 无平方因子 */
    s = sqrt(n);
    if (s * s == n) {
        return 0;
    }

    for (i = 0; i < n_prime_numbers && P[i] <= n; i++) {
        // test i ^ n mod n = i
        if (mod(P[i], n, n) != P[i]) {
            return 0;
        }
    }

    return 1;
}

int main() {
    int n;

    init_prime_number_table();

    scanf("%d", &n);
    while (n) {
        if (is_carmichael_number(n)) {
            printf("The number %d is a Carmichael number.\n", n);
        } else {
            printf("%d is normal.\n", n);
        }

        scanf("%d", &n);
    }
}