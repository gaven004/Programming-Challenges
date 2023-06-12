/*
 * Polynomial Coefficients
 * PC/UVa IDs: 110506/10105
 */

/*
 * 多项式定理应用
 */

#include <stdio.h>

#define MAXN 13

int main() {
    int table[MAXN];
    int n, k;
    int i, e, t;

    /* 初始化阶乘表 */
    table[0] = table[1] = 1;
    for (i = 2; i < MAXN; ++i) {
        table[i] = table[i - 1] * i;
    }

    while (scanf("%d %d", &n, &k) != EOF) {
        t = 1;
        for (i = 1; i <= k; ++i) {
            scanf("%d", &e);
            if (e > 1) {
                t *= table[e];
            }
        }
        printf("%d\n", table[n] / t);
    }
}