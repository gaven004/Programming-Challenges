/*
 * Expressions
 * PC/UVa IDs: 110604/10157
 */

#include <stdio.h>

#define MAXN 151
#define MAXD 151

int main() {
    long long f[MAXN][MAXD];
    int n, d, i;

    for (d = 0; d < MAXD; d++) {
        f[0][d] = 1;
    }

    for (n = 1; n < MAXN; n++) {
        for (d = 0; d < MAXD; d++) {
            f[n][d] = 0;
        }
    }

    /* f(n,d) = sum{f(i, d - 1)*f(n - i - 1, d)} (0<=i<n) */
    for (n = 1; n < MAXN; n++) {
        for (d = 1; d <= MAXD; d++) {
            for (i = 0; i < n; i++) {
                f[n][d] += f[i][d - 1] * f[n - i - 1][d];
            }
        }
    }

    while (scanf("%d %d", &n, &d) == 2) {
        if (n % 2) {
            printf("0\n");
        } else {
            n = n / 2;
            printf("%lld\n", f[n][d] - f[n][d - 1]);
        }
    }
}