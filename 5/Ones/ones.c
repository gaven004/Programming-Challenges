/*
 * Ones
 * PC/UVa IDs: 110504/10127
 */

#include <stdio.h>

int main() {
    int n, c, r;

    while (scanf("%d", &n) != EOF) {
        c = 0, r = 0;
        do {
            r = (r * 10 + 1) % n;
            c++;
        } while (r);
        printf("%d\n", c);
    }
}