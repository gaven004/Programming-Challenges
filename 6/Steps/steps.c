/*
 * Steps
 * PC/UVa IDs: 110608/846
 */

#include <stdio.h>
#include <math.h>

int main() {
    int n, x, y, l, s;

    scanf("%d", &n);
    while (n--) {
        scanf("%d %d", &x, &y);

        if (x == y) {
            printf("%d\n", 0);
            continue;
        }

        l = y - x, s = (int) floor(sqrt(l));

        if (s * s >= l) {
            printf("%d\n", 2 * s - 1);
        } else if (s * (s + 1) >= l) {
            printf("%d\n", 2 * s);
        } else {
            printf("%d\n", 2 * s + 1);
        }
    }
}