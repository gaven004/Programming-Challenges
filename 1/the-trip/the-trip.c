/* 
 * The Trip
 * PC/UVa IDs: 110103/10137
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTS 1000

int expenses[MAX_STUDENTS];

int main(void) {
  int i;
  int n;
  int d, c; /* dollars and cents */
  int s, e; /* sum, exchanged */
  int l, u; /* lower, upper */
  int g, t; /* give, take */

  for (scanf("%d", &n); n; scanf("%d", &n)) {
    s = 0;
    for (i = 0; i < n; i++) {
      scanf("%d.%d", &d, &c);
      expenses[i] = d * 100 + c;
      s += expenses[i];
    }

    l = s / n;
    u = ((l * n == s) ? l : l + 1);

    g = 0, t = 0;
    for (i = 0; i < n; i++) {
      if (expenses[i] > u) {
        t += expenses[i] - u;
      } else if (expenses[i] < l) {
        g += l - expenses[i];
      }
    }

    e = (g > t) ? g : t;
    d = e / 100;
    c = e - d * 100;
    printf("$%d.%02d\n", d, c);
  }

  return EXIT_SUCCESS;
}