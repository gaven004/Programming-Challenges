/*
 * Counting
 * PC/UVa IDs: 110603/10198
 */

#include <stdio.h>
#include <string.h>

#define MAXDIGITS 500 /* maximum length bignum */
#define MAXLENGTH 1001

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

void add_bignum(bignum *a, bignum *b) {
    int carry; /* carry digit */
    int i; /* counter */
    int l; /* lastdigit of sum */

    l = (a->lastdigit > b->lastdigit) ? a->lastdigit : b->lastdigit;

    for (carry = 0, i = 0; i <= l; i++) {
        a->digits[i] = carry + a->digits[i] + b->digits[i];

        if (RADIX <= a->digits[i]) {
            a->digits[i] -= RADIX;
            carry = 1;
        } else {
            carry = 0;
        }
    }

    if (carry > 0) {
        l++;
        a->digits[l] = carry;
    }

    a->lastdigit = l;

    for (i = l + 1; i < MAXDIGITS; i++) {
        a->digits[i] = '\0';
    }

    zero_justify(a);
}

int main() {
    int i, n;

    /* Init */
    parse_bignum(&(F[1]), "2"); /* F[1] = 2 */
    parse_bignum(&(F[2]), "5"); /* F[2] = 5 */
    parse_bignum(&(F[3]), "13"); /* F[3] = 13 */
    /* F(n) = 2*F(n-1) + F(n-2) + F(n-3) */
    for (i = 4; i < MAXLENGTH; ++i) {
        parse_bignum(&(F[i]), "0");
        add_bignum(&(F[i]), &(F[i - 1]));
        add_bignum(&(F[i]), &(F[i - 1]));
        add_bignum(&(F[i]), &(F[i - 2]));
        add_bignum(&(F[i]), &(F[i - 3]));
    }

    while (scanf("%d", &n) != EOF) {
        print_bignum(&(F[n]));
    }
}