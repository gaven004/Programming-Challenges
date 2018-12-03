#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char DOT_MATRIX[10][5][3] = {
  {
    /* 0 */
    {' ', '-',' '},
    {'|', ' ','|'},
    {' ', ' ',' '},
    {'|', ' ','|'},
    {' ', '-',' '},
  },
  {
    /* 1 */
    {' ', ' ',' '},
    {' ', ' ','|'},
    {' ', ' ',' '},
    {' ', ' ','|'},
    {' ', ' ',' '},
  },
  {
    /* 2 */
    {' ', '-',' '},
    {' ', ' ','|'},
    {' ', '-',' '},
    {'|', ' ',' '},
    {' ', '-',' '},
  },
  {
    /* 3 */
    {' ', '-',' '},
    {' ', ' ','|'},
    {' ', '-',' '},
    {' ', ' ','|'},
    {' ', '-',' '},
  },
  {
    /* 4 */
    {' ', ' ',' '},
    {'|', ' ','|'},
    {' ', '-',' '},
    {' ', ' ','|'},
    {' ', ' ',' '},
  },
  {
    /* 5 */
    {' ', '-',' '},
    {'|', ' ',' '},
    {' ', '-',' '},
    {' ', ' ','|'},
    {' ', '-',' '},
  },
  {
    /* 6 */
    {' ', '-',' '},
    {'|', ' ',' '},
    {' ', '-',' '},
    {'|', ' ','|'},
    {' ', '-',' '},
  },
  {
    /* 7 */
    {' ', '-',' '},
    {' ', ' ','|'},
    {' ', ' ',' '},
    {' ', ' ','|'},
    {' ', ' ',' '},
  },
  {
    /* 8 */
    {' ', '-',' '},
    {'|', ' ','|'},
    {' ', '-',' '},
    {'|', ' ','|'},
    {' ', '-',' '},
  },
  {
    /* 9 */
    {' ', '-',' '},
    {'|', ' ','|'},
    {' ', '-',' '},
    {' ', ' ','|'},
    {' ', '-',' '},
  }
};

int main(void) {
  int s, r, n;
  int i, j, k;
  char buff[20];

  for (scanf("%d %s", &s, buff); s; scanf("%d %s", &s, buff)) {
    for (r = 0; r < 5; r++) {
      for (k = (r % 2 ? s : 1); k > 0; k--) {
        for (i = 0; buff[i]; i++) {
          if (i) {
            putchar(' ');
          }
          n = buff[i] - '0';
          putchar(DOT_MATRIX[n][r][0]);
          for (j = 0; j < s; j++) {
            putchar(DOT_MATRIX[n][r][1]);
          }
          putchar(DOT_MATRIX[n][r][2]);
        }
        putchar('\n');
      }
    }
    putchar('\n');
  }

  return EXIT_SUCCESS;
}
