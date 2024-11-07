/*
 * Marbles
 * PC/UVa IDs: 110707/10090
 */

#include <stdio.h>

/*
 * Extended Euclidean Algorithm
 *
 * INPUT
 *   a, b = two non-negative integers
 * OUTPUT
 *   d = the greatest common divisor (GCD) of a and b
 *   x, y = integers such that d = x * a + y * b
 */
int egcd(long long a, long long b, long long *x, long long *y) {
    if (b == 0) {
        *x = 1, *y = 0;
        return a;
    }

    long long q, r, d, xn, yn;
    q = a / b, r = a % b;
    d = egcd(b, r, &xn, &yn);
    *x = yn, *y = xn - q * yn;
    return d;
}

void solve(int n, int n1, int n2, int *m1, int *m2) {
    long long x, y, d, m, dx, dy;

    if (n >= n1 && n >= n2) {
        d = egcd(n1, n2, &x, &y);

        if (n % d == 0) {
            m = n / d, x *= m, y *= m;
            dx = n2 / d, dy = n1 / d;

            if (y >= dy) {
                m = y / dy, y = y - m * dy, x = x + m * dx;
            } else if (y < 0) {
                m = -y / dy, y = y + m * dy, x = x - m * dx;
                if (y < 0) {
                    y = y + dy, x = x - dx;
                }
            }

            if (x >= 0 && y >= 0) {
                *m1 = x, *m2 = y;
                return;
            }
        }
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
