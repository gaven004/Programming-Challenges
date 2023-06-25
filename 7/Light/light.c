/*
 * Light, More Light
 * PC/UVa IDs: 110701/10110
 */

#include <stdio.h>

#define MAXL 20

int T[11] = {0, 3, 9, 31, 99, 316, 999, 3162, 10000, 31622, 65536};

int scan(char *s) {
    int c, l = 0;

    c = getchar();
    while ('0' <= c && c <= '9') {
        *s = c;
        s++, l++;
        c = getchar();
    }

    *s = '\0';
    return l;
}

int is_perfect_square_int(unsigned long long n, int l) {
    unsigned long long x = T[l];

    /* 牛顿迭代法 */
    while (x * x > n) {
        x = (x + n / x) >> 1;
    }

    return x * x == n;
}

int is_perfect_square(char buff[MAXL], int l) {
    char c;
    unsigned int n, s;

    /*
     * (1)平方数的个位数字只能是0，1，4，5，6，9。
     * (2)任何偶数的平方一定能被4整除;任何奇数的平方被4(或8)除余1，即被4除余2或3的数一定不是完全平方数。
     */

    c = buff[l - 1];
    if (c == 2 || c == 3 || c == 7 || c == 8) {
        return 0;
    }

    sscanf(buff, "%u", &n);

    if (c == 0 || c == 4 || c == 6) {
        if (c % 4 != 0) {
            return 0;
        }
    }

    if (c == 1 || c == 5 || c == 9) {
        if (c % 4 != 1) {
            return 0;
        }
    }

    return is_perfect_square_int(n, l);
}

int main() {
    char buff[MAXL];
    int l;

    l = scan(buff);
    while (l > 0 && buff[0] > '0') {
        if (is_perfect_square(buff, l)) {
            puts("yes");
        } else {
            puts("no");
        }

        l = scan(buff);
    }
}