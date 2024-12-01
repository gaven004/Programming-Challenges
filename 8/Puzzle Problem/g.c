//
// 生成Puzzle
// Created by Gaven Auyeu on 2024/11/30.
//

#include <stdio.h>
#include <stdlib.h>

#define SIZE 4
#define N_DIRECTIONS 4

char movement[] = {'L', 'U', 'R', 'D'};
int move_x[] = {-1, 0, 1, 0};
int move_y[] = {0, -1, 0, 1};

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

int move(int puzzle[SIZE][SIZE], int *x, int *y, int direction) {
    int x1 = *x + move_x[direction], y1 = *y + move_y[direction], t = puzzle[y1][x1];
    puzzle[y1][x1] = puzzle[*y][*x], puzzle[*y][*x] = t;
    *x = x1, *y = y1;
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

int main() {
    int puzzle[SIZE][SIZE] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 0}
    };
    print(puzzle);

    int x = 3, y = 3, i, d;

    for (i = 0; i < 20; i++) {
        d = rand() % N_DIRECTIONS;
        if (can_move(x, y, d)) {
            printf("%c\n", movement[d]);
            move(puzzle, &x, &y, d);
            print(puzzle);
        }
    }
}
