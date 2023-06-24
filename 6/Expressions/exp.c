/*
 * Expressions
 * PC/UVa IDs: 110604/10157
 */

/*
 * 涉及高精度运算，最大值有83位
 */

#include <stdio.h>
#include <string.h>

#define MAXDIGITS 85 /* maximum length bignum */
#define RADIX 10

#define MAXN 151
#define MAXD 151

typedef struct {
    char digits[MAXDIGITS]; /* represent the number, in little-endian order */
    int lastdigit; /* index of last digit */
} bignum;

bignum C[MAXN][MAXD];

void print_bignum(bignum *n) {
    int i, j;
    char buff[MAXDIGITS];

    for (i = n->lastdigit, j = 0; i >= 0; i--, j++) {
        buff[j] = '0' + n->digits[i];
    }
    buff[j] = '\0';

    puts(buff);
}

void zero_justify(bignum *n) {
    while ((n->lastdigit > 0) && (n->digits[n->lastdigit] == 0)) {
        n->lastdigit--;
    }
}

void parse_bignum(bignum *n, char *s) {
    int l = strlen(s);

    l--;
    n->lastdigit = l;
    while (*s) {
        n->digits[l] = *s - '0';
        s++, l--;
    }

    for (l = n->lastdigit + 1; l < MAXDIGITS; l++) {
        n->digits[l] = '\0';
    }

    zero_justify(n);
}

void add_bignum(bignum *a, bignum *b, bignum *c) {
    bignum t;
    int carry; /* carry digit */
    int i; /* counter */

    c->lastdigit = (a->lastdigit > b->lastdigit) ? a->lastdigit : b->lastdigit;

    for (carry = 0, i = 0; i <= (c->lastdigit); i++) {
        c->digits[i] = carry + a->digits[i] + b->digits[i];

        if (RADIX <= c->digits[i]) {
            c->digits[i] -= RADIX;
            carry = 1;
        } else {
            carry = 0;
        }
    }

    if (carry > 0) {
        c->lastdigit++;
        c->digits[c->lastdigit] = carry;
    }
}

void subtract_bignum(bignum *a, bignum *b, bignum *c) {
    int borrow;
    int v;
    int i;

    c->lastdigit = a->lastdigit;

    for (borrow = 0, i = 0; i <= (c->lastdigit); i++) {
        v = (a->digits[i] - borrow - b->digits[i]);
        if (v >= 0) {
            borrow = 0;
            c->digits[i] = v;
        } else {
            borrow = 1;
            c->digits[i] = v + RADIX;
        }
    }

    zero_justify(c);
}

void multiply_bignum(bignum *a, bignum *b, bignum *c) {
    int i, j, k, t;
    int m, n;

    m = a->lastdigit + 1, n = b->lastdigit + 1;

    c->lastdigit = m + n - 1;
    for (i = 0; i <= c->lastdigit; i++) {
        c->digits[i] = 0;
    }

    for (j = 0; j < n; ++j) {
        if (b->digits[j] == 0) {
            continue;
        }

        for (k = 0, i = 0; i < m; ++i) {
            t = a->digits[i] * b->digits[j] + c->digits[i + j] + k;
            c->digits[i + j] = t % RADIX;
            k = t / RADIX;
        }

        c->digits[i + j] = k;
    }

    zero_justify(c);
}

void init() {
    int n, d, i;
    bignum t;

    for (d = 0; d < MAXD; d++) {
        parse_bignum(&(C[0][d]), "1");
    }

    for (n = 1; n < MAXN; n++) {
        for (d = 0; d < MAXD; d++) {
            parse_bignum(&(C[n][d]), "0");
        }
    }

    /* f(n,d) = sum{f(i, d - 1)*f(n - i - 1, d)} (0<=i<n) */
    for (n = 1; n < MAXN; n++) {
        for (d = 1; d <= MAXD; d++) {
            for (i = 0; i < n; i++) {
                multiply_bignum(&(C[i][d - 1]), &(C[n - i - 1][d]), &t);
                add_bignum(&(C[n][d]), &t, &(C[n][d]));
            }
        }
    }
}

int main() {
    int n, d;
    bignum t;

    init();

    while (scanf("%d %d", &n, &d) == 2) {
        n = n / 2;
        subtract_bignum(&(C[n][d]), &(C[n][d - 1]), &t);
        print_bignum(&t);
    }
}