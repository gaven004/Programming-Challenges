/*
 * N Queens problem
 */

#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 8

typedef struct {
  int row, column;
} square_t;

int nsolutions;

void print(square_t *s) {
  int r, c;

  for (r = 0; r < BOARD_SIZE; r++, s++) {
    for (c = 0; c < BOARD_SIZE; c++) {
      if (c == s->column) {
        putchar('X');
      } else {
        putchar('O');
      }
    }
    putchar('\n');
  }
  putchar('\n');
}

int check(square_t *solution, int ns, square_t *candidate) {
  int i;

  for (i = 0; i < ns; i++, solution++) {
    if ((solution->column == candidate->column) ||
        (solution->row + solution->column ==
         candidate->row + candidate->column) ||
        (solution->row - solution->column ==
         candidate->row - candidate->column)) {
      return 0;
    }
  }

  return 1;
}

void place(square_t *solution, int ns) {
  int r, c;
  square_t candidate;

  r = ns;

  for (c = 0; c < BOARD_SIZE; c++) {
    candidate.row = r, candidate.column = c;

    if (check(solution, ns, &candidate)) {
      (solution + ns)->row = candidate.row,
                  (solution + ns)->column = candidate.column;

      if (ns + 1 == BOARD_SIZE) {
        nsolutions++;
        print(solution);
      } else {
        place(solution, ns + 1);
      }
    }
  }
}

int main() {
  square_t solution[BOARD_SIZE];
  nsolutions = 0;
  place(solution, 0);
  printf("\n\nTotal solutions: %d\n", nsolutions);
  return 0;
}
