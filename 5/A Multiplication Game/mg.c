/*
 * A Multiplication Game
 * PC/UVa IDs: 110505/847
 */

#include <stdio.h>

int judge(long long n) {
    long long p = 1;

    while (1) {
        p *= 9;
        if (p >= n)
            return 1;

        p *= 2;
        if (p >= n)
            return 0;
    }
}

int main() {
    long long n;

    while (scanf("%lld", &n) != EOF) {
        printf("%s wins.\n", judge(n) ? "Stan" : "Ollie");
    }
}