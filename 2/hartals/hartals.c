/*
 * Hartals
 * PC/UVa IDs: 110203/10050
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int day[3651];

int main() {
  int cases, n, p, h, lost;
  int i, j, r;

  scanf("%d", &cases);

  while (cases--) {
    scanf("%d", &n);
    memset(day, 0, sizeof(day)), lost = 0;

    scanf("%d", &p);
    for (i = 0; i < p; i++) {
      scanf("%d", &h);
      for (j = h; j <= n; j += h) {
        if (!day[j]) {
          day[j] = 1, r = j % 7;
          if (r != 0 && r != 6) {
            lost++;
          }
        }
      }
    }

    printf("%d\n", lost);
  }

  return EXIT_SUCCESS;
}