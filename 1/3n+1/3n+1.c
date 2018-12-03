/* 
 * The 3n + 1 Problem
 * PC/UVa IDs: 110101/100
 */

#include <stdio.h>

#define MAX_VALUE 1000000

/**
 * Cache
 */
int CL[MAX_VALUE + 1];

/**
 * cycle-length of n
 */
int cl(long long n) {
  if (n <= MAX_VALUE && CL[n] > 0) {
    return CL[n];
  }

  int l;
  if (n == 1) {
    l = 1;
  } else if (n % 2 == 0) {
    l = cl(n >> 1) + 1;
  } else {
    l = cl(n * 3 + 1) + 1;
  }

  if (n < MAX_VALUE) {
    CL[n] = l;
  }

  return l;
}

/**
 * maximum cycle length for integers between and including i and j
 * i <= j
 */
int mcl(int i, int j) {
  int k, l, m;

  m = 1;
  for (k = i; k <= j; k++) {
    l = cl(k);
    if (l > m) {
      m = l;
    }
  }

  return m;
}

int main(int argc, char const *argv[]) {
  int i, j, m;

  while (scanf("%d %d", &i, &j) != EOF) {
    m = (i < j) ? mcl(i, j) : mcl(j, i);
    printf("%d %d %d\n", i, j, m);
  }

  return 0;
}
