/*
 * The Priest Mathematician
 * PC/UVa IDs: 110606/10254
 */

#include <stdio.h>
#include <string.h>

#define MAXDIGITS 50 /* maximum length bignum */
#define MAXLENGTH 10001

#define RADIX 10

typedef struct {
    char digits[MAXDIGITS]; /* represent the number, in little-endian order */
    int lastdigit; /* index of last digit */
} bignum;

bignum F[MAXLENGTH];

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

void init() {
    bignum e;
    int i, j, k;

    parse_bignum(&(F[1]), "1");
    parse_bignum(&(e), "2");

    for (i = 2, j = 1, k = 2; i < MAXLENGTH; ++i) {
        add_bignum(&(F[i - 1]), &e, &(F[i]));

        j++;
        if (j > k) {
            j = 1, k++;
            add_bignum(&e, &e, &e);
        }
    }

}

int main() {
    int n;

    init();

    while (scanf("%d", &n) != EOF) {
        print_bignum(&(F[n]));
    }
}