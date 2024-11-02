/*
 * Smith Numbers
 * PC/UVa IDs: 110706/10042
 */

#include <stdio.h>
#include <math.h>

int sum_digits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int check(const int n) {
    int s1, s2, t, i, l;

    t = n, s1 = sum_digits(t), s2 = 0;

    i = 2;
    while (t % i == 0) {
        t = t / i, s2 += i;
        if (s1 < s2) {
            return 0;
        }
    }

    if (s1 == s2) {
        return (t == 1) ? 1 : 0;
    }

    i = 3;
    while (t % i == 0) {
        t = t / i, s2 += i;
        if (s1 < s2) {
            return 0;
        }
    }

    if (s1 == s2) {
        return (t == 1) ? 1 : 0;
    }

    l = sqrt(t) + 1, i = 5; // 由于精度问题，保险起见加1
    while (i <= l) {
        while (t % i == 0) {
            t = t / i, s2 += sum_digits(i);
            if (s1 < s2) {
                return 0;
            }
        }

        if (s1 == s2) {
            return (t == 1) ? 1 : 0;
        }

        i += 2;
        while (t % i == 0) {
            t = t / i, s2 += sum_digits(i);
            if (s1 < s2) {
                return 0;
            }
        }

        if (s1 == s2) {
            return (t == 1) ? 1 : 0;
        }

        i += 4;
    }

    if (t == n) {
        // n为质数
        return 0;
    }

    if (1 < t) {
        if (s1 == s2 + sum_digits(t))
            return 1;
    }

    return 0;
}

int solve(int n) {
    if (n < 3) n = 3;

    while (n++) {
        if (check(n)) return n;
    }
}

int main() {
    int cases, n;

    scanf("%d", &cases);
    while (cases--) {
        scanf("%d", &n);
        printf("%d\n", solve(n));
    }
}
