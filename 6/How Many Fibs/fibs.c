/*
 * How Many Fibs?
 * PC/UVa IDs: 110601/10183
 */

#include <stdio.h>
#include <string.h>

#define MAXDIGITS 105 /* maximum length bignum */
#define MAXLENGTH 1000

#define RADIX 10

typedef struct {
    char digits[MAXDIGITS]; /* represent the number, in little-endian order */
    int lastdigit; /* index of last digit */
} bignum;

bignum table[MAXLENGTH];

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

int compare_bignum(bignum *a, bignum *b) {
    int i;

    if (a->lastdigit > b->lastdigit) {
        return 1;
    }

    if (a->lastdigit < b->lastdigit) {
        return -1;
    }

    for (i = a->lastdigit; i >= 0; i--) {
        if (a->digits[i] > b->digits[i]) {
            return 1;
        }

        if (b->digits[i] > a->digits[i]) {
            return -1;
        }
    }

    return 0;
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

    for (i = c->lastdigit + 1; i < MAXDIGITS; i++) {
        c->digits[i] = '\0';
    }

    zero_justify(c);
}

int main() {
    int i, s;
    char buff_a[MAXDIGITS], buff_b[MAXDIGITS];
    bignum a, b, m;

    parse_bignum(&m,
                 "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");

    parse_bignum(&(table[1]), "1");
    parse_bignum(&(table[2]), "2");

    i = 2;
    do {
        i++;
        add_bignum(&(table[i - 2]), &(table[i - 1]), &(table[i]));
    } while (compare_bignum(&(table[i]), &m) <= 0);

    scanf("%s %s", buff_a, buff_b);
    while (buff_a[0] != '0' || buff_b[0] != '0') {
        parse_bignum(&a, buff_a);
        parse_bignum(&b, buff_b);


        for (i = 1; compare_bignum(&(table[i]), &a) < 0; i++) {
        }
        s = i;

        for (; compare_bignum(&(table[i]), &b) <= 0; i++) {
        }

        printf("%d\n", i - s);

        scanf("%s %s", buff_a, buff_b);
    }
}