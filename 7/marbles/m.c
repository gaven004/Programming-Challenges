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
 *   and d = (x + dx) * a + (y + dy) * b
 */
long long egcd(long long a, long long b, long long *x, long long *y, long long *dx, long long *dy) {
    long long s = 0, t = 1, old_s = 1, old_t = 0;
    long long q, r, m, n;

    while (b != 0) {
        q = a / b, r = a % b;
        m = s - old_s * q, n = t - old_t * q;
        a = b, b = r, s = old_s, t = old_t, old_s = m, old_t = n;
    }

    *x = t, *y = s, *dx = n, *dy = m;
    return a;
}

void solve(long long n, long long n1, long long n2, long long *m1, long long *m2) {
    long long x, y, d, m, dx, dy;

    if (n >= n1 && n >= n2) {
        d = egcd(n1, n2, &x, &y, &dx, &dy);

        if (n % d == 0) {
            m = n / d, x *= m, y *= m;
            m = y / dy, y = y - m * dy, x = x - m * dx;

            if (y < 0) {
                if (dy > 0) {
                    y += dy, x += dx;
                } else {
                    y -= dy, x -= dx;
                }
            }

            if (x >= 0 && y >= 0) {
                *m1 = (int) x, *m2 = (int) y;
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
    long long m1, m2; /* number of type i boxes required */

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
