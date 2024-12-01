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
    int x1 = *x + move_x[direction], y1 = *y + move_y[direction], t = puzzle[y1][x1];
    puzzle[y1][x1] = puzzle[*y][*x], puzzle[*y][*x] = t;
    *x = x1, *y = y1;
}

int back(int puzzle[SIZE][SIZE], int *x, int *y, int direction) {
    int x1 = *x - move_x[direction], y1 = *y - move_y[direction], t = puzzle[y1][x1];
    puzzle[y1][x1] = puzzle[*y][*x], puzzle[*y][*x] = t;
    *x = x1, *y = y1;
}

int cpy(int s[SIZE][SIZE], int t[SIZE][SIZE]) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            t[i][j] = s[i][j];
        }
    }
}

int cmp(int s[SIZE][SIZE], int t[SIZE][SIZE]) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (s[i][j] != t[i][j]) {
                return 1;
            }
        }
    }
    return 0;
}

int check_duplicates(int puzzle[SIZE][SIZE], int x, int y, int sequence[MOST_STEPS], int k, int d) {
    int next[SIZE][SIZE], his[SIZE][SIZE];
    int nx = x, ny = y, hx = x, hy = y;

    cpy(puzzle, next), cpy(puzzle, his);
    move(next, &nx, &ny, d);
    // printf("Next\n", k), print(next);

    for (k--; k >= 0; k--) {
        move(his, &hx, &hy, reverse_move[sequence[k]]);
        // printf("His\n", k), print(his);
        if (cmp(next, his) == 0) {
            return 0;
        }
    }

    return 1;
}

int is_repeat(int puzzle[SIZE][SIZE], int x, int y, int sequence[MOST_STEPS], int k, int direction) {
    for (int dx = move_x[direction], dy = move_y[direction], i = k - 1; i >= 0; i--) {
        dx += move_x[sequence[i]], dy += move_y[sequence[i]];
        if (dx == 0 && dy == 0) {
            // 空块移动回同一位置，进一步检查是否整个Puzzle都重复
            if (!check_duplicates(puzzle, x, y, sequence, k, direction)) {
                return 1;
            }
        }
    }

    return 0;
}

int solve(int puzzle[SIZE][SIZE], int x, int y, int sequence[MOST_STEPS], int k) {
    if (k > MOST_STEPS) {
        puts("Overflow: "), print(puzzle);
        return -1;
    }

    printf("Input puzzle: k=%d\n", k), print(puzzle);

    if (is_a_solution(puzzle)) {
        finished = 1;
        return k;
    }

    for (int d = 0; d < N_DIRECTIONS; d++) {
        if (k > 0 && d == reverse_move[sequence[k - 1]]) {
            // 不走回头路
            continue;
        }

        if (!can_move(x, y, d)) {
            // 不能移动的方向
            continue;
        }

        if (is_repeat(puzzle, x, y, sequence, k, d)) {
            // 环形路线
            continue;
        }

        move(puzzle, &x, &y, d);
        sequence[k] = d;

        printf("Try: %c\n", movement[d]), print(puzzle);

        int r = solve(puzzle, x, y, sequence, k + 1);
        if (r >= 0) {
            return r;
        }

        printf("Would rollback: %d %d\n", x, y), print(puzzle);

        move(puzzle, &x, &y, reverse_move[d]);
        puts("Back: "), print(puzzle);
    }

    return -1;
}

int main() {
    int cases;
    int puzzle[SIZE][SIZE] = {};
    int sequence[MOST_STEPS + 1] = {};
    int x, y, i, j, k;

    scanf("%d", &cases);
    while (cases--) {
        for (i = 0; i < SIZE; i++) {
            for (j = 0; j < SIZE; j++) {
                scanf("%d", &puzzle[i][j]);
                if (puzzle[i][j] == 0) {
                    x = j, y = i;
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
