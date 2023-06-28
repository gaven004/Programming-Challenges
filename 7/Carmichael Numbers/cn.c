/*
 * Carmichael Numbers
 * PC/UVa IDs: 110702/10006
 */

#include <stdio.h>
#include <math.h>

#define MAXN 65000

unsigned int R[MAXN];
int F[MAXN];

int is_composite_number(unsigned int n) {
    int i, l;

    if (n <= 3) {
        return 0;
    }

    if (n % 2 == 0 || n % 3 == 0) {
        return 1;
    }

    l = sqrt(n) + 1; // 由于精度问题，保险起见加1
    for (i = 5; i <= l; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 1;
        }
    }

    return 0;
}

/* get a ^ x mod n */
unsigned int mod(int a, int x, int n) {
    int i;

    if (F[x]) {
        return R[x];
    }

    if (x == 1) {
        R[1] = a, F[1] = 1;
        return a;
    }

    i = x / 2;
    R[x] = (mod(a, i, n) * mod(a, x - i, n)) % n;
    F[x] = 1;

    return R[x];
}

int is_carmichael_number(unsigned int n) {
    unsigned int a;
    int i;

    if (!is_composite_number(n)) {
        return 0;
    }

    for (a = 2; a < n; a++) {
        for (i = 0; i <= n; ++i) {
            F[i] = 0;
        }

        // test a ^ n mod n = a
        if (mod(a, n, n) != a) {
            return 0;
        }
    }

    return 1;
}

int main() {
    int n;

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