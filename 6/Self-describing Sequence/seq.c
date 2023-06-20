/*
 * Steps
 * PC/UVa IDs: 110607/10049
 */

#include <stdio.h>

#define MAXN 2000000000
#define MAXL 1000000

int p[MAXL];

int search(int l, int r, int n) {
    int m = (l + r) / 2;

    if (n > p[m]) {
        return search(m + 1, r, n);
    } else if (n == p[m]) {
        return m;
    } else if (n >= p[m - 1]) {
        return m - 1;
    } else {
        return search(l, m - 1, n);
    }
}

int main() {
    int f, i, j, k, n;

    p[1] = i = f = k = 1;
    do {
        p[i + 1] = p[i] + f;

        i++;
        if (i >= p[k + 1]) {
            f++, k++;
        }
    } while (p[i] < MAXN);

    while (scanf("%d", &n) && n) {
        printf("%d\n", search(1, i, n));
    }
}