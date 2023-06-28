/*
 * Carmichael Numbers
 * PC/UVa IDs: 110702/10006
 */

#include <stdio.h>
#include <math.h>
#include <time.h>

#define MAXN 65000

unsigned int R[MAXN];

int is_composite_number(unsigned int n) {
    unsigned int i, l;

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
    if (x == 1) {
        return a;
    }

    unsigned int i = x / 2;
    unsigned int result = mod(a, i, n);

    result = (result * result) % n;

    if (x - i > i) {
        result = (result * a) % n;
    }

    return result;
}

int is_carmichael_number(unsigned int n) {
    unsigned int a;
    int i;

    if (!is_composite_number(n)) {
        return 0;
    }

    for (a = 2; a < n; a++) {
        // test a ^ n mod n = a
        if (mod(a, n, n) != a) {
            return 0;
        }
    }

    return 1;
}

int main() {
    int n;

    clock_t start, end;

    start = clock();

    scanf("%d", &n);
    while (n) {
        if (is_carmichael_number(n)) {
            printf("The number %d is a Carmichael number.\n", n);
        } else {
            printf("%d is normal.\n", n);
        }

        scanf("%d", &n);
    }

    end = clock();

    printf("\nElapsed: %ld\n", end - start);

}