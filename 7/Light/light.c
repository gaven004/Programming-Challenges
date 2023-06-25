/*
 * Light, More Light
 * PC/UVa IDs: 110701/10110
 */

#include <stdio.h>
#include <math.h>
#include <time.h>

int main() {
    unsigned int n, s;

    clock_t start, end;

    start = clock();

    scanf("%u", &n);
    while (n) {
        s = sqrtf(n);
        puts(s * s == n ? "yes" : "no");

        scanf("%u", &n);
    }


    end = clock();

    printf("\nElapsed: %ld\n", end - start);

}