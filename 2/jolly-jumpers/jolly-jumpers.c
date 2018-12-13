/* 
 * Jolly Jumpers
 * PC/UVa IDs: 110201/10038
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 3000

char flag[MAX_LENGTH];

/* skip the rest of the line */
void _skip() {
  int c;
  while ((c = getchar()) != EOF && c != '\n') {
  }
}

void check(int n) {
  int i;
  int cur, pre, diff;

  if (n <= 1) {
    puts("Jolly");
    return;
  }

  memset(flag, 0, n);
  n--;

  scanf("%d", &pre);
  for (i = 0; i < n; ++i) {
    scanf("%d", &cur);
    diff = (pre > cur) ? (pre - cur) : (cur - pre);

    if (diff < 1 || n < diff || flag[diff]) {
      puts("Not jolly");
      return;
    }

    flag[diff] = 1, pre = cur;
  }

  puts("Jolly");
}

int main(void) {
  int n;

  while (scanf("%d", &n) != EOF) {
    check(n);
    _skip();
  }

  return EXIT_SUCCESS;
}
