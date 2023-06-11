/*
 * Reverse and Add
 * PC/UVa IDs: 110502/10018
 */

#include <stdio.h>

unsigned long reverse(unsigned long n) {
    unsigned long r = 0;

    while (n) {
        r = r * 10 + n % 10;
        n = n / 10;
    }

    return r;
}

int main() {
    int c, s;
    unsigned long n, r;

    for (scanf("%d", &c); c; c--) {
        s = 0, scanf("%lu", &n), r = reverse(n);
        while (n != r) {
            n += r;
            r = reverse(n);
            s++;
        }
        printf("%d %lu\n", s, n);
    }
}