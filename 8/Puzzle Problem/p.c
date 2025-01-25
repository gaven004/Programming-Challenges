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
#define MOST_STEPS 50
#define N_DIRECTIONS 4

#define MASK 0XFLL
#define DEST 0XFEDCBA987654321LL

unsigned long long _1MASK[16], _0MASK[16];

// 'L', 'U', 'R', 'D': 空块与左、上、右、下边的方块对换
char movement[] = {'L', 'U', 'R', 'D'};
char move_x[] = {-1, 0, 1, 0};
char move_y[] = {0, -1, 0, 1};
char reverse_move[] = {2, 3, 0, 1};

typedef struct _node {
    unsigned long long board;
    char sequence[MOST_STEPS];
    char steps, h;
    char x0, y0;
    struct _node *next;
} node_t;

typedef struct {
    unsigned size; /* number of queue elements */
    node_t *head; /* position of head element */
    node_t *tail; /* position of tail element */
} queue_t;

typedef struct {
    queue_t *queues[MOST_STEPS + 1]; /* position of head element */
} priority_queue_t;

/* function to create priority_queue_t. */
priority_queue_t *create_queue() {
    int i;
    priority_queue_t *pq = (priority_queue_t *) malloc(sizeof(priority_queue_t));
    for (i = 1; i <= MOST_STEPS; i++) {
        queue_t *q = (queue_t *) malloc(sizeof(queue_t));
        q->size = 0;
        q->head = NULL;
        q->tail = NULL;
        pq->queues[i] = q;
    }
    return pq;
}

void en_queue(priority_queue_t *pq, node_t *node) {
    queue_t *q = pq->queues[node->h];
    node->next = NULL;
    if (q->size == 0) {
        q->head = node;
    } else {
        q->tail->next = node;
    }
    q->tail = node;
    q->size++;
}

node_t *de_queue(priority_queue_t *pq) {
    int i;
    for (i = 1; i <= MOST_STEPS; i++) {
        queue_t *q = pq->queues[i];
        if (q->size > 0) {
            node_t *x = q->head;
            q->head = q->head->next;
            q->size--;
            return x;
        }
    }
    return NULL;
}

void print(int puzzle[SIZE][SIZE]) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("%d\t", puzzle[i][j]);
        }
        printf("\n");
    }
}

void print_movement(char *sequence, int k) {
    int i;
    for (i = 0; i < k; i++) {
        printf("%c", movement[sequence[i]]);
    }
    printf("\n");
}

void init() {
    int i;
    for (i = 0; i < 16; i++) {
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

void move(node_t *current, node_t *next, int direction) {
    next->x0 = current->x0 + move_x[direction];
    next->y0 = current->y0 + move_y[direction];

    // s：当前空格的位置，t：准备交换的位置
    int si = current->y0 * SIZE + current->x0;
    int ti = next->y0 * SIZE + next->x0;

    // 获取t位置的值，并移位
    unsigned long long v = current->board & _1MASK[ti];
    if (si > ti) {
        v <<= (si - ti) * SIZE;
    } else {
        v >>= (ti - si) * SIZE;
    }

    next->board = current->board & _0MASK[ti] | v;
    int i;
    for (i = 0; i < current->steps; i++) {
        next->sequence[i] = current->sequence[i];
    }
    next->sequence[i] = direction;
    next->h = current->h - heuristic_s(current->board, next->x0, next->y0)
              + heuristic_s(next->board, current->x0, current->y0) + 1;
    next->steps = current->steps + 1;

    // printf("from: [%llx], to: [%llx], d: %c, h: %d\n", current->board, next->board, movement[direction], next->h);
}

int solve(int puzzle[SIZE][SIZE], int x0, int y0) {
    int d;
    priority_queue_t *pq = create_queue();
    node_t *node = (node_t *) malloc(sizeof(node_t));

    node->board = matrix_2_long(puzzle);

    if (DEST == node->board) {
        printf("\n");
        return 0;
    }

    node->steps = 0, node->h = heuristic_l(node->board, x0, y0);
    node->x0 = x0, node->y0 = y0;

    en_queue(pq, node);

    while ((node = de_queue(pq)) != NULL) {
        for (d = 0; d < N_DIRECTIONS; d++) {
            if (node->steps > 0 && d == reverse_move[node->sequence[node->steps - 1]]) {
                // 不走回头路
                continue;
            }

            if (!can_move(node->x0, node->y0, d)) {
                // 不能移动的方向
                continue;
            }

            node_t *next = (node_t *) malloc(sizeof(node_t));
            move(node, next, d);

            if (DEST == next->board) {
                print_movement(next->sequence, next->steps);
                return next->steps;
            }

            if (next->h <= MOST_STEPS) {
                en_queue(pq, next);
            }
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

        if (!is_solvable(board, y0)) {
            puts("This puzzle is not solvable.");
            continue;
        }

        solve(board, x0, y0);
    }
}
