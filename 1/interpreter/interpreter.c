/* 
 * Interpreter
 * PC/UVa IDs: 110106/10033
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int reg[10];
int ram[1000];

void init() {
  int i;

  for (i = 0; i < 10; i++) {
    reg[i] = 0;
  }

  for (i = 0; i < 1000; i++) {
    ram[i] = 0;
  }
}

void getop(int v, int *op1, int *op2) {
  v = v % 100;
  *op1 = v / 10;
  *op2 = v - *op1 * 10;
}

void setv(int *p, int v) { *p = (v < 1000) ? v : v % 1000; }

int main() {
  char buff[10];
  int cases;
  int n;  /* the number of instructions executed */
  int *p; /* pointer of ram */
  int k;  /* RAM address that to be executed */
  int v;  /* value of register of ram */
  int op1, op2;

  fgets(buff, 10, stdin), sscanf(buff, "%d", &cases);
  fgets(buff, 10, stdin); /* the blank line */

  while (cases-- > 0) {
    /* initialize */
    init();

    /* read data */
    p = ram;
    while (fgets(buff, 10, stdin) != NULL && strcmp(buff, "")) {
      sscanf(buff, "%d", p);
      p++;
    }

    /* processing */
    for (n = 1, k = 0; (v = ram[k]) != 100; n++) {
      getop(v, &op1, &op2);

      if (v < 100) {
        /* 0ds, goto the location in register d unless register s contains 0 */
        if (*(reg + op2)) {
          k = *(reg + op1);
          continue;
        }
      } else if (v < 200) {
        /* 100, halt */
      } else if (v < 300) {
        /* 2dn, set register d to n */
        setv(reg + op1, op2);
      } else if (v < 400) {
        /* 3dn, add n to register d */
        setv(reg + op1, *(reg + op1) + op2);
      } else if (v < 500) {
        /* 4dn, multiply register d by n */
        setv(reg + op1, *(reg + op1) * op2);
      } else if (v < 600) {
        /* 5ds, set register d to the value of register s */
        *(reg + op1) = *(reg + op2);
      } else if (v < 700) {
        /* 6ds, add the value of register s to register d */
        setv(reg + op1, *(reg + op1) + *(reg + op2));
      } else if (v < 800) {
        /* 7ds, multiply register d by the value of register s */
        setv(reg + op1, *(reg + op1) * *(reg + op2));
      } else if (v < 900) {
        /* 8da, set register d to the value in RAM whose address is in register
         * a */
        *(reg + op1) = *(ram + *(reg + op2));
      } else {
        /* 9sa, set the value in RAM whose address is in register a to that of
         * register s */
        *(ram + *(reg + op2)) = *(reg + op1);
      }

      k++;
    }

    /* output */
    printf("%d\n", n);

    if (cases) {
      putchar('\n');
    }
  }

  return EXIT_SUCCESS;
}
