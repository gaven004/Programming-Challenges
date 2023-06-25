/*
 * Light, More Light
 * PC/UVa IDs: 110701/10110
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAXL 20

unsigned int T[11] = {0, 3, 9, 31, 99, 316, 999, 3162, 10000, 31622, 65536};

int is_perfect_square_int(unsigned int n, int l) {
    long long x = T[l];

    /* 牛顿迭代法 */
    while (x * x > n) {
        x = (x + n / x) >> 1;
    }

    return x * x == n;
}

int is_perfect_square(char buff[MAXL], int l) {
    char c, b;
    unsigned int n, s;

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
                if (c == 2 || c == 4 || c == 6 || c == 8 || c == 0) {
                    return 0;
                }
                break;
            case 1:
            case 4:
            case 9:
                if (c == 1 || c == 3 || c == 5 || c == 7 || c == 9) {
                    return 0;
                }
                break;
        }
    }

    sscanf(buff, "%u", &n);

    if (c == 0 || c == 4 || c == 6) {
        if (c % 4 != 0) {
            return 0;
        }
    }

    if (c == 1 || c == 5 || c == 9) {
        if (c % 8 != 1) {
            return 0;
        }
    }

    return is_perfect_square_int(n, l);
}

int main() {
    char buff[MAXL];
    int l;

    clock_t start, end;

    start = clock();

    scanf("%s", buff), l = strlen(buff);
    while (l > 0 && buff[0] > '0') {
        if (is_perfect_square(buff, l)) {
            puts("yes");
        } else {
            puts("no");
        }

        scanf("%s", buff), l = strlen(buff);
    }

    end = clock();

    printf("\nElapsed: %ld\n", end - start);

}