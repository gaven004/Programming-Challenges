/*
 * Poker Hands
 * PC/UVa IDs: 110202/10315
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
  HIGH_CARD,
  PAIR,
  TWO_PAIRS,
  THREE_OF_A_KIND,
  STRAIGHT,
  FLUSH,
  FULL_HOUSE,
  FOUR_OF_A_KIND,
  STRAIGHT_FLUSH
};

typedef struct {
  unsigned int HIGH_CARD : 1;
  unsigned int PAIR : 1;
  unsigned int TWO_PAIRS : 1;
  unsigned int THREE_OF_A_KIND : 1;
  unsigned int STRAIGHT : 1;
  unsigned int FLUSH : 1;
  unsigned int FULL_HOUSE : 1;
  unsigned int FOUR_OF_A_KIND : 1;
  unsigned int STRAIGHT_FLUSH : 1;
} FLAG;

typedef struct {
  int category;
  int score;
} rank_t;

void print(char cards[5][3]) {
  printf("%s %s %s %s %s\n", cards[0], cards[1], cards[2], cards[3], cards[4]);
}

void transform(char cards[5][3]) {
  int i;

  for (i = 0; i < 5; ++i) {
    switch (cards[i][0]) {
    case 'T':
      cards[i][0] = '9' + 1;
      break;
    case 'J':
      cards[i][0] = '9' + 2;
      break;
    case 'Q':
      cards[i][0] = '9' + 3;
      break;
    case 'K':
      cards[i][0] = '9' + 4;
      break;
    case 'A':
      cards[i][0] = '9' + 5;
      break;
    default:
      break;
    }
  }
}

rank_t get_rank(char cards[5][3]) {
  int i;
  int t;
  FLAG f = {0};
  rank_t rank;

  rank.category = 0;

  cards[4][2] = 1, t = cards[4][0];
  for (i = 3; i >= 0; i--) {
    cards[i][2] = (cards[i][0] == cards[i + 1][0]) ? cards[i + 1][2] + 1 : 1;
    t = (t << 4) + cards[i][0];
    if (cards[i][2] == 1) {

    } else if (cards[i][2] == 2) {
      if (f.THREE_OF_A_KIND) {
        rank.category = FULL_HOUSE;
        rank.score = cards[i + 2][0];
      } else if (f.PAIR) {
        f.TWO_PAIRS = 1;
        rank.category = TWO_PAIRS;
        rank.score = (rank.score << 4) + cards[i][0];
      } else {
        f.PAIR = 1;
        rank.category = PAIR;
        rank.score = cards[i][0];
      }
    } else if (cards[i][2] == 3) {
      if (f.TWO_PAIRS) {
        /* f.FULL_HOUSE = 1; */
        rank.category = FULL_HOUSE;
      } else {
        f.THREE_OF_A_KIND = 1;
        rank.category = THREE_OF_A_KIND;
      }
      rank.score = cards[i][0];
    } else if (cards[i][2] == 4) {
      /* f.FOUR_OF_A_KIND = 1; */
      rank.category = FOUR_OF_A_KIND;
      rank.score = cards[i][0];
    }
  }

  if (rank.category) {
    if (rank.category == TWO_PAIRS || rank.category == PAIR) {
      rank.score = (rank.score << 20) + t;
    }

    return rank;
  }

  rank.category = HIGH_CARD;
  rank.score = t;

  if (cards[0][0] + 1 == cards[1][0] && cards[1][0] + 1 == cards[2][0] &&
      cards[2][0] + 1 == cards[3][0] && cards[3][0] + 1 == cards[4][0]) {
    f.STRAIGHT = 1;
    rank.category = STRAIGHT;
  }

  if (cards[0][1] == cards[1][1] && cards[1][1] == cards[2][1] &&
      cards[2][1] == cards[3][1] && cards[3][1] == cards[4][1]) {
    /* f.FLUSH = 1; */
    rank.category = f.STRAIGHT ? STRAIGHT_FLUSH : FLUSH;
  }

  return rank;
}

int cmp_hand(char black_hand[5][3], char white_hand[5][3]) {
  rank_t blank_rank, white_rank;

  transform(black_hand);
  qsort(black_hand, 5, 3, (int (*)(const void *, const void *))strcmp);
  /* printf("black_hand: "), print(black_hand); */

  transform(white_hand);
  qsort(white_hand, 5, 3, (int (*)(const void *, const void *))strcmp);
  /* printf("white_hand: "), print(white_hand); */

  blank_rank = get_rank(black_hand), white_rank = get_rank(white_hand);

  return (blank_rank.category == white_rank.category)
             ? blank_rank.score - white_rank.score
             : blank_rank.category - white_rank.category;
}

int main() {
  int i;
  char black_hand[5][3], white_hand[5][3];

  while (scanf("%s %s %s %s %s", black_hand[0], black_hand[1], black_hand[2],
               black_hand[3], black_hand[4]) != EOF) {
    scanf("%s %s %s %s %s", white_hand[0], white_hand[1], white_hand[2],
          white_hand[3], white_hand[4]);

    i = cmp_hand(black_hand, white_hand);
    if (i > 0) {
      puts("Black wins.");
    } else if (i < 0) {
      puts("White wins.");
    } else {
      puts("Tie.");
    }
  }

  return 0;
}
