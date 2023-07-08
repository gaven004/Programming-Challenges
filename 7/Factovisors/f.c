/*
 * Factovisors
 * PC/UVa IDs: 110704/10139
 */

#include <stdio.h>
#include <math.h>

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

int main() {
    int n, m, i, c, s, q, f;

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

        q = m;

        if (q % 2 == 0) {
            c = 1, q = q / 2;
            while (q % 2 == 0) {
                c++, q = q / 2;
            }

            if (check_factors(n, 2, c) == 0) {
                printf("%u does not divide %u!\n", m, n);
                continue;
            }
        }

        if (q % 3 == 0) {
            c = 1, q = q / 3;
            while (q % 3 == 0) {
                c++, q = q / 3;
            }

            if (check_factors(n, 3, c) == 0) {
                printf("%u does not divide %u!\n", m, n);
                continue;
            }
        }

        s = sqrt(m) + 1, f = 1;
        for (i = 5; i <= s && i <= n; i += 4) {
            if (q % i == 0) {
                c = 1, q = q / i;
                while (q % i == 0) {
                    c++, q = q / i;
                }

                if (check_factors(n, i, c) == 0) {
                    f = 0;
                    break;
                }
            }

            i += 2;
            if (q % i == 0) {
                c = 1, q = q / i;
                while (q % i == 0) {
                    c++, q = q / i;
                }

                if (check_factors(n, i, c) == 0) {
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