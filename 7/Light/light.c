/*
 * Light, More Light
 * PC/UVa IDs: 110701/10110
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAXL 20

int is_perfect_square(char buff[MAXL], int l) {
    char c, b;
    unsigned int n, s;

    /*
     * (1)平方数的个位数字只能是0，1，4，5，6，9。
     * (2)任何偶数的平方一定能被4整除;任何奇数的平方被4(或8)除余1，即被4除余2或3的数一定不是完全平方数。
     */

    c = buff[l - 1];
    if (c == '2' || c == '3' || c == '7' || c == '8') {
        return 0;
    }

    if (l > 1) {
        b = buff[l - 2];

        switch (c) {
            case '0':
                if (b != '0') {
                    return 0;
                }
                break;
            case '5':
                if (b != '2') {
                    return 0;
                }
                break;
            case '6':
                if (b == '2' || b == '4' || b == '6' || b == '8' || b == '0') {
                    return 0;
                }
                break;
            case '1':
            case '4':
            case '9':
                if (b == '1' || b == '3' || b == '5' || b == '7' || b == '9') {
                    return 0;
                }
                break;
        }
    }

    sscanf(buff, "%u", &n);

    s = sqrtf(n);
    return s * s == n;
}

int main() {
    char buff[MAXL];
    int l;

    scanf("%s", buff), l = strlen(buff);
    while (l > 0 && buff[0] > '0') {
        if (is_perfect_square(buff, l)) {
            puts("yes");
        } else {
            puts("no");
        }

        scanf("%s", buff), l = strlen(buff);
    }
}