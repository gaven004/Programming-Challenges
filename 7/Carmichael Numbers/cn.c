/*
 * Carmichael Numbers
 * PC/UVa IDs: 110702/10006
 */

#include <math.h>
#include <stdio.h>

#define MAXN 65000

int F[MAXN];

unsigned int n_prime_numbers;
unsigned int P[MAXN];

void init_prime_number_table() {
    int i, j, s;

    F[0] = F[1] = 0;
    for (i = 2; i < MAXN; i++) {
        F[i] = 1;
    }

    s = sqrt(MAXN) + 1, n_prime_numbers = 0;
    for (i = 2; i <= s; i++) {
        if (F[i]) {
            P[n_prime_numbers] = i;
            n_prime_numbers++;
            for (j = i * i; j < MAXN; j += i) {
                F[j] = 0;
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
    unsigned int i;
    unsigned int s;

    if (F[n]) {
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

    /*
     * 只需要判断质数即可，其它的合数，可由公式 xy mod n = (x mod n)(y mod n) mod n 推导出
     * (xy) ^ n mod n = (x ^ n * y ^ n) mod n = (x ^ n mod n)(y ^ n mod n) mod n = xy mod n = xy
     */
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