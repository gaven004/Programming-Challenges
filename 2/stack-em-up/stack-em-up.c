/*
 * Stack ’em Up
 * PC/UVa IDs: 110205/10205
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 80

char *cards[53] = {"",
                   "2 of Clubs",
                   "3 of Clubs",
                   "4 of Clubs",
                   "5 of Clubs",
                   "6 of Clubs",
                   "7 of Clubs",
                   "8 of Clubs",
                   "9 of Clubs",
                   "10 of Clubs",
                   "Jack of Clubs",
                   "Queen of Clubs",
                   "King of Clubs",
                   "Ace of Clubs",
                   "2 of Diamonds",
                   "3 of Diamonds",
                   "4 of Diamonds",
                   "5 of Diamonds",
                   "6 of Diamonds",
                   "7 of Diamonds",
                   "8 of Diamonds",
                   "9 of Diamonds",
                   "10 of Diamonds",
                   "Jack of Diamonds",
                   "Queen of Diamonds",
                   "King of Diamonds",
                   "Ace of Diamonds",
                   "2 of Hearts",
                   "3 of Hearts",
                   "4 of Hearts",
                   "5 of Hearts",
                   "6 of Hearts",
                   "7 of Hearts",
                   "8 of Hearts",
                   "9 of Hearts",
                   "10 of Hearts",
                   "Jack of Hearts",
                   "Queen of Hearts",
                   "King of Hearts",
                   "Ace of Hearts",
                   "2 of Spades",
                   "3 of Spades",
                   "4 of Spades",
                   "5 of Spades",
                   "6 of Spades",
                   "7 of Spades",
                   "8 of Spades",
                   "9 of Spades",
                   "10 of Spades",
                   "Jack of Spades",
                   "Queen of Spades",
                   "King of Spades",
                   "Ace of Spades"};

int buff1[53], buff2[53];
int shuffles[101][53];

int main() {
  int cases, n, k, i, j, v;
  int *source, *target, *temp;
  char line[80];

  scanf("%d", &cases);
  while (cases--) {
    for (i = 1; i <= 52; ++i) {
      buff1[i] = i;
    }

    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
      for (j = 1; j <= 52; ++j) {
        scanf("%d", &(shuffles[i][j]));
      }
    }

    fgets(line, LINE_LENGTH, stdin);

    source = buff1, target = buff2;

    while (fgets(line, LINE_LENGTH, stdin) && line[0] >= '0') {
      sscanf(line, "%d", &k);

      for (i = 1; i <= 52; ++i) {
        *(target + i) = *(source + shuffles[k][i]);
      };
      temp = source, source = target, target = temp;
    }

    for (i = 1; i <= 52; ++i) {
      puts(cards[*(source + i)]);
    }

    if (cases) {
      putchar('\n');
    }
  }

  return EXIT_SUCCESS;
}