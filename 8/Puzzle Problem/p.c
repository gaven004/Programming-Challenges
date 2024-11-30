/*
 * 15-Puzzle Problem
 * PC/UVa IDs: 110802/10181
 *
 * Created by gaven on 2024/11/26.
 */

#include <stdio.h>

#define SIZE 4
#define MOST_STEPS 50
#define N_DIRECTIONS 4

// 'L', 'U', 'R', 'D': 空块与左、上、右、下边的方块对换
char movement[] = {'L', 'U', 'R', 'D'};
int move_x[] = {-1, 0, 1, 0};
int move_y[] = {0, -1, 0, 1};
int reverse_move[] = {2, 3, 0, 1};

int finished = 0;

int print(int puzzle[SIZE][SIZE]) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("%d\t", puzzle[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int is_a_solution(int puzzle[SIZE][SIZE]) {
    int i, j;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (puzzle[i][j] != i * SIZE + j + 1) {
                return (i == SIZE - 1) && (j == SIZE - 1) && (puzzle[SIZE - 1][SIZE - 1] == 0);
            }
        }
    }

    return 0;
}

int can_move(int x, int y, int direction) {
    switch (direction) {
        case 0:
            return 0 < x;
        case 1:
            return 0 < y;
        case 2:
            return x < SIZE - 1;
        case 3:
            return y < SIZE - 1;
    }
    return 0;
}

int move(int puzzle[SIZE][SIZE], int *x, int *y, int direction) {
    int x1 = *x + move_x[direction], y1 = *y + move_y[direction], t = puzzle[x1][y1];
    puzzle[x1][y1] = puzzle[*x][*y], puzzle[*x][*y] = t;
    *x = x1, *y = y1;
}

int back(int puzzle[SIZE][SIZE], int *x, int *y, int direction) {
    int x1 = *x - move_x[direction], y1 = *y - move_y[direction], t = puzzle[x1][y1];
    puzzle[x1][y1] = puzzle[*x][*y], puzzle[*x][*y] = t;
    *x = x1, *y = y1;
}

int solve(int puzzle[SIZE][SIZE], int x, int y, int sequence[MOST_STEPS], int k) {
    if (k > MOST_STEPS) {
        return -1;
    }

    if (is_a_solution(puzzle)) {
        finished = 1;
        return k;
    }

    for (int d = 0; d < N_DIRECTIONS; d++) {
        if (k > 0 && d == reverse_move[sequence[k - 1]]) {
            // 不走回头路
            continue;
        }

        if (can_move(x, y, d)) {
            print(puzzle);
            move(puzzle, &x, &y, d);
            print(puzzle);
            sequence[k] = d;
            int r = solve(puzzle, x, y, sequence, k + 1);
            if (r >= 0) {
                return r;
            }
            back(puzzle, &x, &y, d);
            print(puzzle);
            return -1;
        }
    }

    return -1;
}

int main() {
    int cases;
    int puzzle[SIZE][SIZE];
    int sequence[MOST_STEPS];
    int x, y, i, j, k;

    scanf("%d", &cases);
    while (cases--) {
        for (i = 0; i < SIZE; i++) {
            for (j = 0; j < SIZE; j++) {
                scanf("%d", &puzzle[i][j]);
                if (puzzle[i][j] == 0) {
                    x = i, y = j;
                }
            }
        }

        k = solve(puzzle, x, y, sequence, 0);

        if (k >= 0) {
            for (i = 0; i < k; i++) {
                printf("%c", movement[sequence[i]]);
            }
            printf("\n");
        } else {
            puts("This puzzle is not solvable.");
        }
    }
}
