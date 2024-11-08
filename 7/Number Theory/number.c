#include <stdio.h>
#include <math.h>

int is_prime(unsigned int n) {
    unsigned int i, l;

    if (n <= 3) {
        return 1;
    }

    if (n % 2 == 0 || n % 3 == 0) {
        return 0;
    }

    l = sqrt(n) + 1; // 由于精度问题，保险起见加1
    for (i = 5; i <= l; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 0;
        }
    }

    return 1;
}

void prime_factorization(unsigned int n) {
    unsigned int i, l;

    if (n <= 3) {
        printf("%u\n", n);
        return;
    }

    while ((n % 2) == 0) {
        printf("2 ");
        n = n / 2;
    }

    while ((n % 3) == 0) {
        printf("3 ");
        n = n / 3;
    }

    l = sqrt(n) + 1, i = 5; // 由于精度问题，保险起见加1
    while (i <= l) {
        while ((n % i) == 0) {
            printf("%u ", i);
            n = n / i;
        }

        i += 2;
        while ((n % i) == 0) {
            printf("%u ", i);
            n = n / i;
        }

        i += 4;
    }


    if (1 < n) {
        printf("%u\n", n);
    }
}

/* Greatest Common Divisor */
unsigned int gcd(unsigned int m, unsigned int n) {
    unsigned int r;

    if (n > m) {
        r = m, m = n, n = r;
    }

    r = m % n;
    while (r) {
        m = n, n = r, r = m % n;
    }

    return n;
}

/* Least Common Multiple */
unsigned int lcm(unsigned int m, unsigned int n) {
    return m / gcd(m, n) * n;
}

/*
 * Extended Euclidean Algorithm
 *
 * INPUT
 *   a, b = two non-negative integers
 * OUTPUT
 *   d = the greatest common divisor (GCD) of a and b
 *   x, y = integers such that d = x * a + y * b
 */
int egcd(int a, int b, int *x, int *y) {
    int s = 0, t = 1, old_s = 1, old_t = 0;
    int q, r, m, n;

    while (b != 0) {
        q = a / b, r = a % b;
        m = s - old_s * q, n = t - old_t * q;
        a = b, b = r, s = old_s, t = old_t, old_s = m, old_t = n;
    }

    *x = t, *y = s;
    return a;
}

int egcd_r(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1, *y = 0;
        return a;
    }

    int q, r, d, xn, yn;
    q = a / b, r = a % b;
    d = egcd_r(b, r, &xn, &yn);
    *x = yn, *y = xn - q * yn;
    return d;
}

int main() {
    int n = 823, x, y;

    if (is_prime(n)) {
        printf("%d is a prime number.\n", n);
    } else {
        printf("%d is not a prime number.\n", n);
    }

    prime_factorization(12345);

    n = gcd(544, 119);
    printf("%u\n", n);

    n = lcm(24, 36);
    printf("%u\n", n);

    n = egcd(1914,899, &x, &y);
    printf("%d = %d * %d + %d * %d\n", n, 1914, x, 899, y);
}
