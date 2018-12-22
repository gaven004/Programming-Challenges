/*
 * Permutation, https://en.wikipedia.org/wiki/Permutation
 *
 * Generation in lexicographic order
 */

#include <stdio.h>

#define LENGTH 5

void pirnt(int *p, int l) {
  for (; l > 0; l--, p++) {
    printf("%d ", *p);
  }
  putchar('\n');
}

int permNext(int *pb, int *pe) {
  register int *pk, *pl, t;

  /* Find the largest index k such that a[k] < a[k + 1] */
  t = *pe;
  for (pk = pe - 1; pk >= pb; --pk) {
    if (*pk < t) {
      break;
    } else {
      t = *pk;
    }
  }

  /* If no such index exists, the permutation is the last permutation. */
  if (pk < pb) {
    return 0;
  }

  /* Find the largest index l such that a[k] < a[l]. */
  for (pl = pe; pl >= pb; --pl) {
    if (*pk < *pl) {
      break;
    }
  }

  /* Swap the value of a[k] with that of a[l]. */
  t = *pk, *pk = *pl, *pl = t;

  /* Reverse the sequence from a[k + 1] up to and including the final element
   * a[n]. */
  for (pk++, pl = pe; pk < pl; ++pk, --pl) {
    t = *pk, *pk = *pl, *pl = t;
  }

  return 1;
}

int main() {
  int items[LENGTH] = {0, 1, 2, 3, 4};

  pirnt(items, LENGTH);
  while (permNext(items, items + LENGTH - 1)) {
    pirnt(items, LENGTH);
  }

  return 0;
}
