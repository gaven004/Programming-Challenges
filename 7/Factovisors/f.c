/*
 * Factovisors
 * PC/UVa IDs: 110704/10139
 */

#include <stdio.h>
#include <math.h>

#define MAXN 65536

int F[MAXN];

int n_prime_numbers;
unsigned int P[MAXN];

int check_factors(int n, int f, int e) {
    int c;

    c = 0;
    while (n >= f) {
        n /= f;
        c += n;

        if (c >= e) {
            return 1;
        }
    }

    return 0;
}

void init_prime_number_table() {
    unsigned int i, j;

    F[0] = F[1] = 0;
    for (i = 2; i < MAXN; i++) {
        F[i] = 1;
    }

    n_prime_numbers = 0;
    for (i = 2; i < MAXN; i++) {
        if (F[i]) {
            P[n_prime_numbers] = i;
            n_prime_numbers++;
            for (j = i * i; j < MAXN; j += i) {
                F[j] = 0;
            }
        }
    }
}

int main() {
    unsigned int n, m, i, c, s, q, f;

    init_prime_number_table();

    while (scanf("%u %u", &n, &m) != EOF) {
        /*
         * 在 https://www.udebug.com/UVa/10139 上，对于 m = 0 时的判断有问题
         * 按定义：a divides b if there exists an integer k such that k * a = b
         * n! > 0，0 没办法整除 n!
         */
        if (m == 0) {
            printf("%u does not divide %u!\n", m, n);
            continue;
        }

        if (m <= n) {
            printf("%u divides %u!\n", m, n);
            continue;
        }

        if (n < 2) {
            if (m < 2) {
                printf("%u divides %u!\n", m, n);
            } else {
                printf("%u does not divide %u!\n", m, n);
            }
            continue;
        }

        s = sqrt(m) + 1, q = m, f = 1;
        for (i = 0; i < n_prime_numbers && P[i] <= s; ++i) {
            if (q % P[i] == 0) {
                if (P[i] > n) {
                    f = 0;
                    break;
                }

                c = 1, q = q / P[i];
                while (q % P[i] == 0) {
                    c++, q = q / P[i];
                }

                if (check_factors(n, P[i], c) == 0) {
                    f = 0;
                    break;
                }
            }
        }

        if (f == 0) {
            printf("%u does not divide %u!\n", m, n);
        } else if (n < q) {
            printf("%u does not divide %u!\n", m, n);
        } else {
            printf("%u divides %u!\n", m, n);
        }
    }
}