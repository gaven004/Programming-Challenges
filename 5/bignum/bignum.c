//
// Created by Gaven Auyeu on 2023/6/5.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXDIGITS 100 /* maximum length bignum */

/*
 * -1 for negative, or 1 for positive. zero must have a signum of 1.
 * This is necessary to ensures that there is exactly one representation for each bignum value.
 */
#define POSITIVE 1 /* positive sign bit */
#define NEGATIVE -1 /* negative sign bit */
#define ZERO 0 /* zero sign bit */

#define RADIX 10

typedef struct {
    char digits[MAXDIGITS]; /* represent the number, in little-endian order */
    int signbit; /* POSITIVE, NEGATIVE or ZERO */
    int lastdigit; /* index of last digit */
} bignum;

int parse_bignum(bignum *n, char *s);

int zero_justify(bignum *n);

int print_bignum(bignum *n);

int copy_bignum(bignum *a, bignum *b);

int negate_bignum(bignum *a, bignum *b);

int compare_bignum(bignum *a, bignum *b);

int add_bignum(bignum *a, bignum *b, bignum *c);

int subtract_bignum(bignum *a, bignum *b, bignum *c);

int multiply_bignum(bignum *a, bignum *b, bignum *c);

int divide_bignum(bignum *a, bignum *b, bignum *c);

int test(int (*operation)(bignum *, bignum *, bignum *)) {
    char buff[100];
    int r;
    bignum a, b, c, d;

    while (scanf("%s", buff) != EOF) {
        parse_bignum(&a, buff);
        print_bignum(&a);

        scanf("%s", buff); // +
        printf(" %s ", buff);

        scanf("%s", buff);
        parse_bignum(&b, buff);
        print_bignum(&b);

        scanf("%s", buff); // =
        printf(" , ");

        scanf("%s", buff);
        parse_bignum(&c, buff);
        printf("expected: ");
        print_bignum(&c);

        operation(&a, &b, &d);
        printf(", actual: ");
        print_bignum(&d);

        r = compare_bignum(&c, &d);
        printf(", result: %d\n", r);
    }
}

int main() {
    bignum a, b, c;

/*
    parse_bignum(&a, "3142");
    parse_bignum(&b, "53");
    divide_bignum(&a, &b, &c);
    print_bignum(&c);
*/

/*
    test(add_bignum);
    test(multiply_bignum);
*/
    test(divide_bignum);

    return EXIT_SUCCESS;
}

int zero_justify(bignum *n) {
    while ((n->lastdigit > 0) && (n->digits[n->lastdigit] == 0)) {
        n->lastdigit--;
    }

    if ((n->lastdigit == 0) && (n->digits[0] == 0)) {
        n->signbit = POSITIVE;
    }
}

int print_bignum(bignum *n) {
    int i;

    zero_justify(n);

    if (n->signbit == NEGATIVE) {
        printf("-");
    }

    for (i = n->lastdigit; i >= 0; i--) {
        printf("%c", '0' + n->digits[i]);
    }
}

int parse_bignum(bignum *n, char *s) {
    int l = strlen(s);

    if ('+' == *s) {
        n->signbit = POSITIVE;
        s++, l--;
    } else if ('-' == *s) {
        n->signbit = NEGATIVE;
        s++, l--;
    } else {
        n->signbit = POSITIVE;
    }

    if (l <= 0 || MAXDIGITS < l) {
        fprintf(stderr, "Error: Not a valid bignum\n");
        exit(EXIT_FAILURE);
    }

    l--;
    n->lastdigit = l;
    while (*s) {
        if (*s < '0' || '9' < *s) {
            fprintf(stderr, "Error: Not a valid bignum\n");
            exit(EXIT_FAILURE);
        }

        n->digits[l] = *s - '0';
        s++, l--;
    }

    for (l = n->lastdigit + 1; l < MAXDIGITS; l++) {
        n->digits[l] = '\0';
    }

    zero_justify(n);
}

int copy_bignum(bignum *a, bignum *b) {
    int i;

    b->signbit = a->signbit;
    b->lastdigit = a->lastdigit;

    for (i = 0; i < MAXDIGITS; ++i) {
        b->digits[i] = a->digits[i];
    }
}

int negate_bignum(bignum *a, bignum *b) {
    int i;

    if (POSITIVE == a->signbit) {
        b->signbit = NEGATIVE;
    } else {
        b->signbit = POSITIVE;
    }

    b->lastdigit = a->lastdigit;

    for (i = 0; i < MAXDIGITS; ++i) {
        b->digits[i] = a->digits[i];
    }
}

int compare_bignum(bignum *a, bignum *b) {
    int i;

    if (a->signbit > b->signbit) {
        return POSITIVE;
    }

    if (a->signbit < b->signbit) {
        return NEGATIVE;
    }

    if (a->lastdigit > b->lastdigit) {
        return (a->signbit);
    }

    if (a->lastdigit < b->lastdigit) {
        return -(a->signbit);
    }

    for (i = a->lastdigit; i >= 0; i--) {
        if (a->digits[i] > b->digits[i]) {
            return (a->signbit);
        }

        if (b->digits[i] > a->digits[i]) {
            return -(a->signbit);
        }
    }

    return ZERO;
}

int add_bignum(bignum *a, bignum *b, bignum *c) {
    bignum t;
    int carry; /* carry digit */
    int i; /* counter */

    if (a->signbit == b->signbit) {
        c->signbit = a->signbit;
        c->lastdigit = (a->lastdigit > b->lastdigit) ? a->lastdigit : b->lastdigit;

        for (carry = 0, i = 0; i <= (c->lastdigit); i++) {
            c->digits[i] = carry;

            if (i <= a->lastdigit) {
                c->digits[i] += a->digits[i];
            }

            if (i <= b->lastdigit) {
                c->digits[i] += b->digits[i];
            }

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

        zero_justify(c);
    } else {
        if (a->signbit == POSITIVE) {
            b->signbit = POSITIVE;
            subtract_bignum(a, b, c);
            b->signbit = NEGATIVE;
        } else {
            a->signbit = POSITIVE;
            subtract_bignum(b, a, c);
            a->signbit = NEGATIVE;
        }
    }
}

int subtract_bignum(bignum *a, bignum *b, bignum *c) {
    int borrow;
    int v;
    int i;

    if (a->signbit == NEGATIVE || b->signbit == NEGATIVE) {
        b->signbit = -(b->signbit);
        add_bignum(a, b, c);
        b->signbit = -(b->signbit);
        return EXIT_SUCCESS;
    }

    v = compare_bignum(a, b);

    if (v == POSITIVE) {
        c->signbit = a->signbit;
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
    } else if (v == NEGATIVE) {
        subtract_bignum(b, a, c);
        c->signbit = -(c->signbit);
    } else {
        c->signbit = POSITIVE;
        c->lastdigit = 0;
        c->digits[0] = '\0';
    }
}

int multiply_bignum(bignum *a, bignum *b, bignum *c) {
    int i, j, k, t;
    int m, n;

    m = a->lastdigit + 1, n = b->lastdigit + 1;

    c->lastdigit = m + n - 1;
    if (MAXDIGITS - 1 < c->lastdigit) {
        fprintf(stderr, "Error: overflow\n");
        exit(EXIT_FAILURE);
    }

    c->signbit = a->signbit * b->signbit;
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

int divide_bignum(bignum *a, bignum *b, bignum *c) {
    bignum u, v;
    int d, i, j, k, m, n, q, r, t;

    if (b->lastdigit == 0 && b->digits[0] == 0) {
        fprintf(stderr, "Error: divide by zero\n");
        exit(EXIT_FAILURE);
    }

    if (a->lastdigit + 1 == MAXDIGITS) {
        fprintf(stderr, "Error: overflow\n");
        exit(EXIT_FAILURE);
    }

    copy_bignum(a, &u);
    copy_bignum(b, &v);

    if (a->signbit == b->signbit) {
        c->signbit = POSITIVE;
    } else {
        c->signbit = NEGATIVE;
    }

    u.signbit = POSITIVE;
    v.signbit = POSITIVE;

    t = compare_bignum(&u, &v);

    if (t == NEGATIVE) {
        c->lastdigit = 0;
        c->digits[0] = 0;
    } else if (t == 0) {
        c->lastdigit = 0;
        c->digits[0] = 1;
    } else {
        /* Knuth算法，计算机程序设计艺术，第二卷，4.3 多精度算术，算法D */

        n = v.lastdigit + 1;
        m = u.lastdigit + 1 - n;

        c->lastdigit = m;
        for (i = 0; i <= m; ++i) {
            c->digits[i] = 0;
        }

        d = RADIX / (v.digits[v.lastdigit] + 1);

        for (k = 0, i = 0; i <= u.lastdigit; ++i) {
            r = d * u.digits[i];
            u.digits[i] = r % RADIX + k;
            k = r / RADIX;
        }
        u.digits[i] = k;

        for (k = 0, i = 0; i <= v.lastdigit; ++i) {
            r = d * v.digits[i];
            v.digits[i] = r % RADIX + k;
            k = r / RADIX;
        }
        v.digits[i] = k;

        for (j = m; j >= 0; j--) {
            t = u.digits[j + n] * RADIX + u.digits[j + n - 1];
            q = t / v.digits[n - 1];
            r = t % v.digits[n - 1];

            do {
                if (q == RADIX || q * v.digits[n - 2] > RADIX * r + u.digits[j + n - 2]) {
                    q--, r += v.digits[n - 1];
                } else {
                    break;
                }
            } while (r < RADIX);

            for (k = 0, i = 0; i < n; ++i) {
                t = u.digits[j + i] - q * v.digits[i] + k;
                if (t >= 0) {
                    u.digits[j + i] = t;
                    k = 0;
                } else {
                    k = t / RADIX;
                    u.digits[j + i] = t % RADIX;
                    if (u.digits[j + i] < 0) {
                        u.digits[j + i] += RADIX;
                        k--;
                    }
                }
            }
            u.digits[j + i] = u.digits[j + i] + k;

            c->digits[j] = q;

            if (u.digits[j + i] < 0) {
                c->digits[j]--;

                for (k = 0, i = 0; i < n; ++i) {
                    t = u.digits[j + i] + v.digits[i] + k;
                    if (t < RADIX) {
                        u.digits[j + i] = t;
                        k = 0;
                    } else {
                        u.digits[j + i] = t - RADIX;
                        k = 1;
                    }
                }
                u.digits[j + i] = u.digits[j + i] - k;
            }
        }
    }

    zero_justify(c);
}