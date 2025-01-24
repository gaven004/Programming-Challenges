/*
 * 15-Puzzle Problem
 * PC/UVa IDs: 110802/10181
 *
 * Created by gaven on 2024/11/26.
 */

/*
 * https://mathworld.wolfram.com/15Puzzle.html
 *
 * https://oi-wiki.org/search/astar/
 * https://www.geeksforgeeks.org/a-search-algorithm/
 */
#include <stdlib.h>
#include <stdio.h>

#define SIZE 4
#define MOST_STEPS 45
#define N_DIRECTIONS 4

#define MASK 15LL
#define DEST 0XFEDCBA987654321LL

#define CAPACITY 10000000

unsigned long long _1MASK[16], _0MASK[16];

int dest_x[] = {3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2};
int dest_y[] = {3, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3};

// 'L', 'U', 'R', 'D': 空块与左、上、右、下边的方块对换
char movement[] = {'L', 'U', 'R', 'D'};
int move_x[] = {-1, 0, 1, 0};
int move_y[] = {0, -1, 0, 1};
int reverse_move[] = {2, 3, 0, 1};

typedef struct {
    int board[SIZE][SIZE];
    int sequence[MOST_STEPS];
    int steps;
    int h;
    int x0, y0;
} node_t;

typedef struct {
    unsigned capacity;
    node_t *items; /* body of queue */
    int head; /* position of head element */
    int tail; /* position of tail element */
    int size; /* number of queue elements */
} queue_t;

void cpy_board(int s[SIZE][SIZE], int t[SIZE][SIZE]) {
    int x, y;
    for (y = 0; y < SIZE; y++) {
        for (x = 0; x < SIZE; x++) {
            t[x][y] = s[x][y];
        }
    }
}

void cpy_queue(int s[MOST_STEPS], int t[MOST_STEPS], int steps) {
    int i;
    for (i = 0; i < steps; i++) {
        t[i] = s[i];
    }
}

/* function to create a queue of given capacity. */
queue_t *create_queue(unsigned capacity) {
    queue_t *queue = (queue_t *) malloc(sizeof(queue_t));
    if (!queue) {
        fprintf(stderr, "Error: Out of space!!! Exiting...\n");
        exit(EXIT_FAILURE);
    }

    queue->capacity = capacity;
    queue->size = 0, queue->head = 0, queue->tail = 0;
    queue->items = (node_t *) malloc(queue->capacity * sizeof(node_t));
    if (!queue->items) {
        fprintf(stderr, "Error: Out of space!!! Exiting...\n");
        exit(EXIT_FAILURE);
    }

    return queue;
}

/* queue is full when size is equal to the capacity */
int is_full(queue_t *queue) { return queue->size == queue->capacity; }

/* queue is empty when size is equal to 0 */
int is_empty(queue_t *queue) { return queue->size == 0; }

void en_queue(queue_t *queue, int board[SIZE][SIZE], int sequence[MOST_STEPS], int steps, int x0, int y0, int h) {
    if (is_full(queue)) {
        puts("Warning: queue overflow enqueue!!!");
        exit(0);
    }

    cpy_board(board, queue->items[queue->tail].board);
    cpy_queue(sequence, queue->items[queue->tail].sequence, steps);
    queue->items[queue->tail].steps = steps;
    queue->items[queue->tail].x0 = x0;
    queue->items[queue->tail].y0 = y0;
    queue->items[queue->tail].h = h;

    queue->tail++;
    if (queue->tail == queue->capacity) {
        queue->tail = 0;
    }
    queue->size++;
}

node_t *de_queue(queue_t *queue) {
    node_t *x;

    if (is_empty(queue)) {
        puts("Warning: empty queue dequeue!!!");
        exit(0);
    }

    x = &(queue->items[queue->head++]);
    if (queue->head == queue->capacity) {
        queue->head = 0;
    }
    queue->size--;

    return (x);
}

void print(int puzzle[SIZE][SIZE]) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("%d\t", puzzle[i][j]);
        }
        printf("\n");
    }
    // printf("\n");
}

void print_movement(int sequence[MOST_STEPS], int k) {
    int i;
    for (i = 0; i < k; i++) {
        printf("%c", movement[sequence[i]]);
    }
    printf("\n");
}

void init() {
    for (int i = 0; i < 16; i++) {
        _1MASK[i] = MASK << (i * SIZE);
        _0MASK[i] = ~_1MASK[i];
    }
}

unsigned long long matrix_2_long(int puzzle[SIZE][SIZE]) {
    unsigned long long l = 0LL;

    int x, y, i = 0;

    for (y = 0; y < SIZE; y++) {
        for (x = 0; x < SIZE; x++) {
            l += (i == 0 ? (unsigned long long) puzzle[y][x] : (unsigned long long) puzzle[y][x] << i);
            i += SIZE;
        }
    }

    return l;
}

void long_2_matrix(unsigned long long l, int puzzle[SIZE][SIZE]) {
    int x, y;

    for (y = 0; y < SIZE; y++) {
        for (x = 0; x < SIZE; x++) {
            puzzle[y][x] = (int) (l & MASK);
            l >>= SIZE;
        }
    }
}

int is_a_solution(int puzzle[SIZE][SIZE]) {
    int x, y;

    for (y = 0; y < SIZE; y++) {
        for (x = 0; x < SIZE; x++) {
            if (x != dest_x[puzzle[y][x]] || y != dest_y[puzzle[y][x]]) {
                return 0;
            }
        }
    }

    return 1;
}

int distance(int x0, int y0, int x1, int y1) {
    return (x0 > x1 ? x0 - x1 : x1 - x0) + (y0 > y1 ? y0 - y1 : y1 - y0);
}

int heuristic_s(unsigned long long l, int x0, int y0) {
    int x1, y1, v;
    l >>= (y0 * SIZE + x0) * SIZE;
    v = (int) (l & MASK) - 1;
    y1 = v / SIZE, x1 = v % SIZE;
    return distance(x0, y0, x1, y1);
}

int heuristic_l(unsigned long long l, int x0, int y0) {
    int x, y, h = 0;

    for (y = 0; y < SIZE; y++) {
        for (x = 0; x < SIZE; x++) {
            if (y != y0 || x != x0) {
                h += heuristic_s(l, x, y);
            }
        }
    }

    return h;
}

int heuristic(int src[SIZE][SIZE]) {
    int x, y, h = 0;

    // print(src);

    for (y = 0; y < SIZE; y++) {
        for (x = 0; x < SIZE; x++) {
            if (src[y][x]) {
                // printf("y = %d, x = %d, v = %d, d = %d\n", y, x, src[y][x],
                //        distance(x, y, dest_x[src[y][x]], dest_y[src[y][x]]));
                h += distance(x, y, dest_x[src[y][x]], dest_y[src[y][x]]);
            }
        }
    }

    return h;
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

// void move(int puzzle[SIZE][SIZE], int *x, int *y, int direction) {
//     int x1 = *x + move_x[direction], y1 = *y + move_y[direction], t = puzzle[y1][x1];
//     puzzle[y1][x1] = puzzle[*y][*x], puzzle[*y][*x] = t;
//     *x = x1, *y = y1;
// }

unsigned long long move(unsigned long long board, int *x, int *y, int direction) {
    int x1 = *x + move_x[direction], y1 = *y + move_y[direction];
    // s：当前空格的位置，t：准备交换的位置
    int s = *y * SIZE + *x, t = y1 * SIZE + x1;
    // 获取t位置的值，并移位
    unsigned long long v = board & _1MASK[t];
    if (s > t) {
        v <<= (s - t) * SIZE;
    } else {
        v >>= (t - s) * SIZE;
    }
    board &= _0MASK[t], board |= v;
    *x = x1, *y = y1;
    return board;
}

int solve(int puzzle[SIZE][SIZE], int x0, int y0, int sequence[MOST_STEPS]) {
    queue_t *queue;
    node_t *node;
    int k, f, m, d;

    if (is_a_solution(puzzle)) {
        return k;
    }

    m = heuristic(puzzle);
    queue = create_queue(CAPACITY);
    en_queue(queue, puzzle, sequence, 0, x0, y0, m);

    while (!is_empty(queue)) {
        puts("\nde_queue");
        node = de_queue(queue);
        k = node->steps;
        x0 = node->x0;
        y0 = node->y0;
        m = node->h;
        cpy_board(node->board, puzzle);
        cpy_queue(node->sequence, sequence, k);

        puts("current board:");
        print(puzzle);
        puts("current movement:");
        print_movement(sequence, k);
        printf("current heuristic: %d\n", m);

        for (d = 0; d < N_DIRECTIONS; d++) {
            if (k > 0 && d == reverse_move[sequence[k - 1]]) {
                // 不走回头路
                continue;
            }

            if (!can_move(x0, y0, d)) {
                // 不能移动的方向
                continue;
            }

            // move(puzzle, &x0, &y0, d);
            sequence[k] = d;

            puts("\nnew board:");
            print(puzzle);
            puts("movement:");
            print_movement(sequence, k + 1);

            if (is_a_solution(puzzle)) {
                return k + 1;
            }

            f = heuristic(puzzle);
            printf("heuristic: %d\n", f);

            if (f + k <= MOST_STEPS) {
                puts("en_queue");
                en_queue(queue, puzzle, sequence, k + 1, x0, y0, f);
                // m = f;
            }

            // move(puzzle, &x0, &y0, reverse_move[d]);
        }
    }

    return -1;
}

/*
 * https://mathworld.wolfram.com/15Puzzle.html
 */
int is_solvable(int puzzle[SIZE][SIZE], int y) {
    int x0, y0, x1, y1;
    int i, s = 0;

    for (y0 = 0; y0 < SIZE; y0++) {
        for (x0 = 0; x0 < SIZE; x0++) {
            i = puzzle[y0][x0];
            if (i > 1) {
                x1 = x0 + 1, y1 = y0;
                if (x1 == SIZE) {
                    x1 = 0, y1++;
                }

                while (y1 < SIZE) {
                    if (puzzle[y1][x1]) {
                        if (i > puzzle[y1][x1]) {
                            s++;
                        }
                    }

                    x1++;
                    if (x1 == SIZE) {
                        x1 = 0, y1++;
                    }
                }
            }
        }
    }

    return (s + y + 1) % 2 == 0;
}

int main() {
    int cases;
    int board[SIZE][SIZE] = {};
    int sequence[MOST_STEPS] = {};
    int x, y, x0, y0, k, i;

    init();

    scanf("%d", &cases);
    while (cases--) {
        for (y = 0; y < SIZE; y++) {
            for (x = 0; x < SIZE; x++) {
                scanf("%d", &board[y][x]);
                if (board[y][x] == 0) {
                    x0 = x, y0 = y;
                }
            }
        }

        int f = heuristic(board);
        printf("heuristic: %d\n", f);

        f = heuristic_l(matrix_2_long(board), x0, y0);
        printf("heuristic: %d\n", f);


        // if (!is_solvable(board, y0)) {
        //     puts("This puzzle is not solvable.");
        //     continue;
        // }

        // k = solve(board, x0, y0, sequence);
        // if (k >= 0) {
        //     print_movement(sequence, k);
        // } else {
        //     puts("This puzzle is not solvable.");
        // }
    }
}
