/*
* Summation of Four Primes
 * PC/UVa IDs: 110705/10168
 */

#include <stdio.h>

#define MAXN 10000001
#define MAX_SQRT_N 3162

#define N_PRIMES 4

char F[MAXN];
int expressed[N_PRIMES];

/**
 * Sieve of Eratosthenes algorithm
 */
void init_prime_number_table() {
    int i;

    F[2] = 1;
    for (i = 3; i < MAXN; i += 2) {
        F[i] = 1;
    }

    for (i = 9; i < MAXN; i += 6) {
        F[i] = 0;
    }

    for (i = 5; i <= MAX_SQRT_N; i += 4) {
        if (F[i]) {
            for (int k = i * i, s = 2 * i; k < MAXN; k += s) {
                F[k] = 0;
            }
        }

        i = i + 2;
        if (F[i]) {
            for (int k = i * i, s = 2 * i; k < MAXN; k += s) {
                F[k] = 0;
            }
        }
    }
}

/**
 * Goldbach’sconjecture
 */
int express(int n) {
    if (n & 1) {
        n -= 5;
        expressed[0] = 2, expressed[1] = 3;
    } else {
        n -= 4;
        expressed[0] = expressed[1] = 2;
    }

    int i = 2;
    if (F[n - i]) {
        expressed[2] = i, expressed[3] = n - i;
        return 1;
    }

    i = 3;
    if (F[n - i]) {
        expressed[2] = i, expressed[3] = n - i;
        return 1;
    }

    const int e = n / 2;
    for (i = 5; i <= e; i += 4) {
        if (F[i] && F[n - i]) {
            expressed[2] = i, expressed[3] = n - i;
            return 1;
        }

        i += 2;
        if (F[i] && F[n - i]) {
            expressed[2] = i, expressed[3] = n - i;
            return 1;
        }
    }

    return 0;
}

int main() {
    int n;

    init_prime_number_table();

    while (scanf("%d", &n) != EOF) {
        if (express(n)) {
            printf("%d %d %d %d\n", expressed[0], expressed[1], expressed[2], expressed[3]);
        } else {
            printf("Impossible.\n");
        }
    }
}
