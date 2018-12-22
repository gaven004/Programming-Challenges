/*
 * Division
 * UVa 725
 */
#include <stdio.h>

#define MAX_VALUE 98765
#define MIN_VALUE 10000

int over, found;

void print(int *s, int l) {
  int i;
  for (i = 0; i < l; i++) {
    putchar(*s++ + '0');
  }
  putchar('\n');
}

void copy_ex(int *s, int *t, int l, int k) {
  int i;
  for (i = 0; i < l; i++) {
    if (i != k) {
      *t = *s;
      t++;
    }
    s++;
  }
}

int convert(int *s, int l) {
  int i, v;
  for (v = i = 0; i < l; i++) {
    v = v * 10 + *s++;
  }
  return v;
}

int match(int *s, int l, int t) {
  int c, r, i, *p;
  int e[10];

  c = 0;
  while (t) {
    r = t % 10;

    /* check the duplicate */
    for (i = 0; i < c; i++) {
      if (r == e[i]) {
        return 0;
      }
    }

    /* does exists? */
    for (p = s, i = 0; i < l; i++, p++) {
      if (*p == r) {
        return 0;
      };
    }

    e[c++] = r, t = t / 10;
  }

  return 1;
}

void check(int selected[], int ns, int quotient) {
  int dividend, divisor;

  divisor = convert(selected, ns);
  dividend = divisor * quotient;

  if (dividend < MIN_VALUE) {
    return;
  }

  if (dividend > MAX_VALUE) {
    over = 1;
    return;
  }

  if (match(selected, ns, dividend)) {
    found = 1;
    printf("%05d / %05d = %d\n", dividend, divisor, quotient);
  }
}

void select(int selected[], int ns, int candidate[], int nc, int total,
            int quotient) {
  int i;
  int dump[nc];

  for (i = 0; i < nc; i++) {
    selected[ns] = candidate[i];

    if (ns + 1 == total) {
      check(selected, total, quotient);
    } else {
      copy_ex(candidate, dump, nc, i);
      select(selected, ns + 1, dump, nc - 1, total, quotient);
    }

    if (over) {
      return;
    }
  }
}

int main() {
  int n, c = 0;
  int selected[10];
  int candidate[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  while (scanf("%d", &n) != EOF && n) {
    if (c++) {
      putchar('\n');
    }

    over = found = 0;
    select(selected, 0, candidate, 10, 5, n);

    if (!found) {
      printf("There are no solutions for %d.\n", n);
    }
  }

  return 0;
}
