#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIMENSION 250

char canvas[DIMENSION + 1][DIMENSION + 1];

void swap(int *i, int *j) {
  int t = *i;
  *i = *j;
  *j = t;
}

void C(int m, int n) {
  int x, y;
  for (y = 1; y <= n; y++) {
    for (x = 1; x <= m; x++) {
      canvas[y][x] = 'O';
    }
  }
}

void L(int x, int y, char c) { canvas[y][x] = c; }

void V(int x, int y1, int y2, char c) {
  int y;

  if (y1 > y2) {
    swap(&y1, &y2);
  }

  for (y = y1; y <= y2; y++) {
    canvas[y][x] = c;
  }
}

void H(int x1, int x2, int y, char c) {
  int x;

  if (x1 > x2) {
    swap(&x1, &x2);
  }

  for (x = x1; x <= x2; x++) {
    canvas[y][x] = c;
  }
}

void K(int x1, int y1, int x2, int y2, char c) {
  int x, y;

  if (x1 > x2) {
    swap(&x1, &x2);
  }

  if (y1 > y2) {
    swap(&y1, &y2);
  }

  for (y = y1; y <= y2; y++) {
    for (x = x1; x <= x2; x++) {
      canvas[y][x] = c;
    }
  }
}

void F(int m, int n, int x, int y, char c) {
  char o = canvas[y][x];
  if (o == c) {
    return;
  }

  canvas[y][x] = c;

  if (y > 1 && o == canvas[y - 1][x]) {
    F(m, n, x, y - 1, c);
  }

  if (y < n && o == canvas[y + 1][x]) {
    F(m, n, x, y + 1, c);
  }

  if (x > 1 && o == canvas[y][x - 1]) {
    F(m, n, x - 1, y, c);
  }

  if (x < m && o == canvas[y][x + 1]) {
    F(m, n, x + 1, y, c);
  }
}

void S(char const *name, int m, int n) {
  int x, y;

  printf("%s\n", name);

  for (y = 1; y <= n; y++) {
    for (x = 1; x <= m; x++) {
      putchar(canvas[y][x]);
    }
    putchar('\n');
  }
}

int main(void) {
  char name[100], c;
  int m, n;
  int x1, y1, x2, y2;

  for (scanf("%c", &c); c != 'X'; scanf("%c", &c)) {
    switch (c) {
    case 'I':
      scanf("%d %d", &m, &n);
      C(m, n);
      break;
    case 'C':
      C(m, n);
      break;
    case 'L':
      scanf("%d %d %c", &x1, &y1, &c);
      L(x1, y1, c);
      break;
    case 'V':
      scanf("%d %d %d %c", &x1, &y1, &y2, &c);
      V(x1, y1, y2, c);
      break;
    case 'H':
      scanf("%d %d %d %c", &x1, &x2, &y1, &c);
      H(x1, x2, y1, c);
      break;
    case 'K':
      scanf("%d %d %d %d %c", &x1, &y1, &x2, &y2, &c);
      K(x1, y1, x2, y2, c);
      break;
    case 'F':
      scanf("%d %d %c", &x1, &y1, &c);
      F(m, n, x1, y1, c);
      break;
    case 'S':
      scanf("%s", name);
      S(name, m, n);
      break;
    default:
      break;
    }
  }

  return EXIT_SUCCESS;
}