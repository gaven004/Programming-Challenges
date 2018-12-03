
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_LENGTH 200
#define MAX_LENGTH_OF_NAME 100
#define MAX_NUMBER_OF_CANDIDATES 20
#define MAX_LINES 1000

int main(void) {
  int cases;
  char buff[BUFFER_LENGTH], *p_buff;

  char names[MAX_NUMBER_OF_CANDIDATES + 1][MAX_LENGTH_OF_NAME];
  int contents[MAX_LINES][MAX_NUMBER_OF_CANDIDATES], *p_contents[MAX_LINES];
  int score[MAX_NUMBER_OF_CANDIDATES + 1];

  int n_candidates, n_lines;

  int high, low;

  int i, j;

  fgets(buff, BUFFER_LENGTH, stdin), sscanf(buff, "%d", &cases);
  fgets(buff, BUFFER_LENGTH, stdin); /* the blank line */
  while (cases-- > 0) {
    /* scan n_candidates */
    fgets(buff, BUFFER_LENGTH, stdin), sscanf(buff, "%d", &n_candidates);

    /* initialize */
    for (i = 1; i <= n_candidates; i++) {
      score[i] = 0;
    }

    /* read data */
    for (i = 1; i <= n_candidates; i++) {
      fgets(names[i], MAX_LENGTH_OF_NAME, stdin);
    }

    n_lines = 0;
    while (fgets(buff, BUFFER_LENGTH, stdin) != NULL && strcmp(buff, "\n")) {
      for (p_buff = buff, i = 0; i < n_candidates; i++) {
        sscanf(p_buff, "%d", &(contents[n_lines][i]));
        p_buff = (contents[n_lines][i] < 10) ? p_buff + 2 : p_buff + 3;
      }
      n_lines++;
    }

    /* processing */

    /* count first choices */
    for (i = 0; i < n_lines; i++) {
      p_contents[i] = contents[i];
      score[*p_contents[i]]++;
    }

    while (1) {
      high = 0, low = n_lines;
      for (i = 1; i <= n_candidates; i++) {
        if (score[i] > high) {
          high = score[i];
        }

        if (score[i] >= 0 && score[i] < low) {
          low = score[i];
        }
      }

      if (high * 2 > n_lines || high == low) {
        /* one candidate receives more than 50% of the vote,
         * or until all remaining candidates are tied */
        break;
      }

      /* all candidates tied for the lowest number of votes are eliminated */
      for (i = 1; i <= n_candidates; i++) {
        if (score[i] == low) {
          score[i] = -1;
        }
      }

      /* Ballots ranking these candidates first are recounted in favor of their
       * highest-ranked non-eliminated candidate */
      for (i = 0; i < n_lines; i++) {
        if (score[*p_contents[i]] < 0) {
          while (score[*p_contents[i]] < 0) {
            p_contents[i]++;
          }
          score[*p_contents[i]]++;
        }
      }
    }

    /* output */
    for (i = 1; i <= n_candidates; i++) {
      if (score[i] == high) {
        printf(names[i]);
      }
    }

    if (cases) {
      putchar('\n');
    }
  }

  return EXIT_SUCCESS;
}
