/*
 * Light, More Light
 * PC/UVa IDs: 110701/10110
 */

#include <stdio.h>

#define MAXL 20

unsigned int T[11] = {0, 3, 9, 31, 99, 316, 999, 3162, 10000, 31622, 65536};

int scan(char *s, unsigned int *p) {
    int c, l = 0;

    *p = 0, c = getchar();
    while ('0' <= c) {
        *s = c - '0', *p = *p * 10 + *s;
        s++, l++;
        c = getchar();
    }

    return l;
}

int is_perfect_square_int(unsigned int n, int l) {
    long long x = T[l];

    /* 牛顿迭代法 */
    while (x * x > n) {
        x = (x + n / x) >> 1;
    }

    return x * x == n;
}

int is_perfect_square(char buff[MAXL], int l, unsigned int n) {
    char c, b;
    unsigned int s;

    /*
     * (1)平方数的个位数字只能是0，1，4，5，6，9。
     * (2)任何偶数的平方一定能被4整除;任何奇数的平方被4(或8)除余1，即被4除余2或3的数一定不是完全平方数。
     */

    c = buff[l - 1];
    if (c == 2 || c == 3 || c == 7 || c == 8) {
        return 0;
    }

    if (l > 1) {
        b = buff[l - 2];

        switch (c) {
            case 0:
                if (b != 0) {
                    return 0;
                }
                break;
            case 5:
                if (b != 2) {
                    return 0;
                }
                break;
            case 6:
                if (b == 2 || b == 4 || b == 6 || b == 8 || b == 0) {
                    return 0;
                }
                break;
            case 1:
            case 4:
            case 9:
                if (b == 1 || b == 3 || b == 5 || b == 7 || b == 9) {
                    return 0;
                }
                break;
        }
    }

    if (c == 0 || c == 4 || c == 6) {
        if (n % 4 != 0) {
            return 0;
        }
    }

    if (c == 1 || c == 5 || c == 9) {
        if (n % 8 != 1) {
            return 0;
        }
    }

    return is_perfect_square_int(n, l);
}

int main() {
    char buff[MAXL];
    int l;
    unsigned int n;

    l = scan(buff, &n);
    while (l > 0 && n > 0) {
        if (is_perfect_square(buff, l, n)) {
            puts("yes");
        } else {
            puts("no");
        }

        l = scan(buff, &n);
    }
}