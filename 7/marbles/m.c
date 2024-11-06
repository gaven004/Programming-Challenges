/*
 * Marbles
 * PC/UVa IDs: 110707/10090
 */

#include <stdio.h>

/*
 * Extended Euclidean Algorithm
 * d = ax + by
 */
int egcd(int a, int b, int *d, int *x, int *y) {
    int u, v, q, r, m, n;

    *x = 0, *y = 1, u = 1, v = 0;
    while (b) {
        q = a / b, r = a % b;

        a = b, b = r;
        *x = u, *y = v;

    }

    *d = a;
}

void solve(int n, int n1, int n2, int *m1, int *m2) {
    int i, j, d;

    if (n >= n1 && n >= n2) {
    }

    *m1 = 0, *m2 = 0;
}

int main() {
    int n; /* n marbles */
    int c1, c2; /* costs */
    int n1, n2; /* capacity */
    int m1, m2; /* number of type i boxes required */

    for (scanf("%d", &n); n; scanf("%d", &n)) {
        scanf("%d %d", &c1, &n1);
        scanf("%d %d", &c2, &n2);

        /* 比较单价 */
        if ((long long) c1 * n2 <= (long long) c2 * n1) {
            solve(n, n1, n2, &m1, &m2);
            if (m1 || m2) {
                printf("%d %d\n", m1, m2);
            } else {
                printf("failed\n");
            }
        } else {
            solve(n, n2, n1, &m2, &m1);
            if (m1 || m2) {
                printf("%d %d\n", m1, m2);
            } else {
                printf("failed\n");
            }
        }
    }
}
