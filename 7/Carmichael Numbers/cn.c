/*
 * Carmichael Numbers
 * PC/UVa IDs: 110702/10006
 */

#include <math.h>
#include <stdio.h>

#define MAXN 65000

int P[MAXN];

void init_prime_number_table() {
    int i, j, s;

    P[0] = P[1] = 0;
    for (i = 2; i < MAXN; i++) {
        P[i] = 1;
    }

    s = sqrt(MAXN) + 1;
    for (i = 2; i <= s; i++) {
        if (P[i]) {
            for (j = i * i; j < MAXN; j += i) {
                P[j] = 0;
            }
        }
    }
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

    if (P[n]) {
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

    for (i = 2; i < n; i++) {
        if (P[i]) {
            // test i ^ n mod n = i
            if (mod(i, n, n) != i) {
                return 0;
            }
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