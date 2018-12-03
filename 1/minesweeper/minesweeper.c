/*
 * Minesweeper
 * PC/UVa IDs: 110102/10189
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 100

char field[MAX_SIZE][MAX_SIZE];

/* m characters, n lines */
void init(int m, int n) {
  for (int y = 0; y < n; y++) {
    for (int x = 0; x < m; x++) {
      field[y][x] = '0';
    }
  }
}

void out(int f, int m, int n) {
  if (f > 1) {
    putchar('\n');
  }

  printf("Field #%d:\n", f);

  for (int y = 0; y < n; y++) {
    for (int x = 0; x < m; x++) {
      putchar(field[y][x]);
    }
    putchar('\n');
  }
}

/* place mine */
void mine(int x, int y, int m, int n) {
  field[y][x] = '*';

  int x1 = (x > 0) ? x - 1 : x;
  int y1 = (y > 0) ? y - 1 : y;
  int x2 = (x < m - 1) ? x + 1 : x;
  int y2 = (y < n - 1) ? y + 1 : y;

  for (y = y1; y <= y2; y++) {
    for (x = x1; x <= x2; x++) {
      if (field[y][x] != '*') {
        field[y][x]++;
      }
    }
  }
}

int main(void) {
  char buff[MAX_SIZE + 2];
  int m, n;  /* m characters, n lines */
  int f = 0; /* fields */

  for (gets(buff), sscanf(buff, "%d %d", &n, &m); m && n;
       gets(buff), sscanf(buff, "%d %d", &n, &m)) {

    /* initialize */
    init(m, n);
    f++;

    /* read data & process */
    for (int y = 0; y < n; y++) {
      gets(buff);
      for (int x = 0; x < m; x++) {
        if (buff[x] == '*') {
          mine(x, y, m, n);
        }
      }
    }

    /* output */
    out(f, m, n);
  }

  return EXIT_SUCCESS;
}
