/* 
 * Check the Check
 * PC/UVa IDs: 110107/10196
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WHITE_KING_IN_CHECK -1
#define BLACK_KING_IN_CHECK 1

typedef struct {
  int x, y;
  char p;
} piece_t;

char board[8][8];

int check_pawn(piece_t piece, piece_t king, int type) {
  return (king.y == piece.y - type &&
          (king.x == piece.x + 1 || king.x == piece.x - 1))
             ? type
             : 0;
}

int check_knight(piece_t piece, piece_t king, int type) {
  return ((piece.x - 2 == king.x && piece.y - 1 == king.y) ||
          (piece.x - 1 == king.x && piece.y - 2 == king.y) ||
          (piece.x + 1 == king.x && piece.y - 2 == king.y) ||
          (piece.x + 2 == king.x && piece.y - 1 == king.y) ||
          (piece.x - 2 == king.x && piece.y + 1 == king.y) ||
          (piece.x - 1 == king.x && piece.y + 2 == king.y) ||
          (piece.x + 1 == king.x && piece.y + 2 == king.y) ||
          (piece.x + 2 == king.x && piece.y + 1 == king.y))
             ? type
             : 0;
}

int check_bishop(piece_t piece, piece_t king, int type) {
  int x, y, x1, y1, x2, y2;

  if (piece.x + piece.y == king.x + king.y) {
    if (piece.x > king.x) {
      x1 = king.x + 1, y1 = king.y - 1, x2 = piece.x;
    } else {
      x1 = piece.x + 1, y1 = piece.y - 1, x2 = king.x;
    }

    for (x = x1, y = y1; x < x2; x++, y--) {
      if ('.' != board[y][x]) {
        return 0;
      }
    }

    return type;
  } else if (piece.x - piece.y == king.x - king.y) {
    if (piece.x > king.x) {
      x1 = king.x + 1, y1 = king.y + 1, x2 = piece.x;
    } else {
      x1 = piece.x + 1, y1 = piece.y + 1, x2 = king.x;
    }

    for (x = x1, y = y1; x < x2; x++, y++) {
      if ('.' != board[y][x]) {
        return 0;
      }
    }

    return type;
  } else {
    return 0;
  }
}

int check_rook(piece_t piece, piece_t king, int type) {
  int i, f, t;

  if (piece.x == king.x) {
    if (piece.y > king.y) {
      f = king.y + 1, t = piece.y;
    } else {
      f = piece.y + 1, t = king.y;
    }

    for (i = f; i < t; i++) {
      if ('.' != board[i][king.x]) {
        return 0;
      }
    }

    return type;
  } else if (piece.y == king.y) {
    if (piece.x > king.x) {
      f = king.x + 1, t = piece.x;
    } else {
      f = piece.x + 1, t = king.x;
    }

    for (i = f; i < t; i++) {
      if ('.' != board[king.y][i]) {
        return 0;
      }
    }

    return type;
  } else {
    return 0;
  }
}

int check_queen(piece_t piece, piece_t king, int type) {
  return check_rook(piece, king, type) ? type : check_bishop(piece, king, type);
}

int main() {
  int nbp, nwp; /* number of black pieces, and white pieces */
  piece_t black_pieces[64], white_pieces[64];

  piece_t pbk, pwk; /* position of black king , and white king */

  int is_not_empty = 1; /* is not empty board */

  int game_number = 1;

  int check;
  /* -1,white king is in check;
      1,black king is in check;
      0,no king is in check */

  int x, y, i;

  char c, buff[20];

  while (is_not_empty) {
    is_not_empty = 0;
    nbp = nwp = 0;
    check = 0;
    pbk.x = pbk.y = pwk.x = pwk.y = -1;

    for (y = 0; y < 8; y++) {
      for (x = 0; x < 8; x++) {
        scanf("%c", &c);
        board[y][x] = c;
        if ('.' != c) {
          is_not_empty = 1;

          switch (c) {
          case 'k':
            pbk.x = x, pbk.y = y;
            break;
          case 'K':
            pwk.x = x, pwk.y = y;
            break;
          case 'p':
          case 'n':
          case 'b':
          case 'r':
          case 'q':
            black_pieces[nbp].x = x, black_pieces[nbp].y = y,
            black_pieces[nbp].p = c, nbp++;
            break;
          case 'P':
          case 'N':
          case 'B':
          case 'R':
          case 'Q':
            white_pieces[nwp].x = x, white_pieces[nwp].y = y,
            white_pieces[nwp].p = c, nwp++;
            break;
          }
        }
      }
      fgets(buff, 20, stdin);
    }

    if (is_not_empty) {
      for (i = 0; !check && i < nbp; i++) {
        switch (black_pieces[i].p) {
        case 'p':
          check = check_pawn(black_pieces[i], pwk, WHITE_KING_IN_CHECK);
          break;
        case 'r':
          check = check_rook(black_pieces[i], pwk, WHITE_KING_IN_CHECK);
          break;
        case 'b':
          check = check_bishop(black_pieces[i], pwk, WHITE_KING_IN_CHECK);
          break;
        case 'n':
          check = check_knight(black_pieces[i], pwk, WHITE_KING_IN_CHECK);
          break;
        case 'q':
          check = check_queen(black_pieces[i], pwk, WHITE_KING_IN_CHECK);
          break;
        default:
          break;
        }
      }

      for (i = 0; !check && i < nwp; i++) {
        switch (white_pieces[i].p) {
        case 'P':
          check = check_pawn(white_pieces[i], pbk, BLACK_KING_IN_CHECK);
          break;
        case 'R':
          check = check_rook(white_pieces[i], pbk, BLACK_KING_IN_CHECK);
          break;
        case 'B':
          check = check_bishop(white_pieces[i], pbk, BLACK_KING_IN_CHECK);
          break;
        case 'N':
          check = check_knight(white_pieces[i], pbk, BLACK_KING_IN_CHECK);
          break;
        case 'Q':
          check = check_queen(white_pieces[i], pbk, BLACK_KING_IN_CHECK);
          break;
        default:
          break;
        }
      }

      printf("Game #%d: ", game_number);

      switch (check) {
      case 1:
        printf("black king is in check.\n");
        break;
      case -1:
        printf("white king is in check.\n");
        break;
      default:
        printf("no king is in check.\n");
        break;
      }
      game_number++;

      fgets(buff, 20, stdin);
    }
  }

  return EXIT_SUCCESS;
}