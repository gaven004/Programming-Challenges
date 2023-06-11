/*
 * Primary Arithmetic
 * PC/UVa IDs: 110501/10035
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXDIGITS 12 /* maximum length bignum */

int scan(char *s) {
    int c, l = 0;

    c = getchar();
    while ('0' <= c && c <= '9') {
        *s = c - '0';
        s++, l++;
        c = getchar();
    }

    return l;
}

/*
 * la >= lb
 */
int count(char a[MAXDIGITS], int la, char b[MAXDIGITS], int lb) {
    int c = 0, k = 0, i = la - 1, j = lb - 1;

    while (j >= 0) {
        if (a[i] + b[j] + k > 9) {
            c++, k = 1;
        } else {
            k = 0;
        }
        i--, j--;
    }

    while (i >= 0) {
        if (a[i] + k > 9) {
            c++, k = 1;
        } else {
            break;
        }
        i--;
    }

    if (c > 1) {
        printf("%d carry operations.\n", c);
    } else if (c) {
        printf("1 carry operation.\n");
    } else {
        printf("No carry operation.\n");
    }
}

int main() {
    char a[MAXDIGITS], b[MAXDIGITS];
    int la, lb;

    la = scan(a), lb = scan(b);
    while (a[0] != '\0' || b[0] != '\0') {
        if (la >= lb) {
            count(a, la, b, lb);
        } else {
            count(b, lb, a, la);
        }
        la = scan(a), lb = scan(b);
    }
}