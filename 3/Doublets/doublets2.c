/*
 * Doublets
 * PC/UVa IDs: 110307/10150
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_LENGTH 100
#define MAX_LENGTH_OF_WORD 16
#define MAX_NUMBER_OF_WORDS 25143

typedef struct
{
    int top;
    int items[MAX_NUMBER_OF_WORDS + 1];
} stack;

void init_stack(stack *s)
{
    s->top = -1;
}

int is_empty_stack(stack *s) { return s->top == -1; }

void push(stack *s, int i)
{
    s->items[++(s->top)] = i;
}

int pop(stack *s)
{
    return s->items[(s->top)--];
}

typedef struct
{
    int *items;
    int first;
    int last;
    int count;
    int capacity;
    int iterator;
} queue;

queue *create_queue(int capacity)
{
    queue *q = (queue *)malloc(sizeof(queue));
    if (!q)
    {
        fprintf(stderr, "Error: Out of space!!! Exiting...\n");
        exit(EXIT_FAILURE);
    }

    q->capacity = capacity;
    q->count = 0, q->first = 0, q->last = 0, q->iterator = 0;
    q->items = (int *)malloc(q->capacity * sizeof(int));
    if (!q->items)
    {
        fprintf(stderr, "Error: Out of space!!! Exiting...\n");
        exit(EXIT_FAILURE);
    }

    return q;
}

void init_queue(queue *q)
{
    q->first = 0;
    q->last = 0;
    q->count = 0;
    q->iterator = 0;
}

void reset_iterator(queue *q)
{
    q->iterator = q->first;
}

void enqueue(queue *q, int x)
{
    if (q->count + 1 >= q->capacity)
    {
        q->capacity = q->capacity * 2;
        int *dest = (int *)malloc(q->capacity * sizeof(int));
        memcpy(dest, q->items, q->count * sizeof(int));
        free(q->items);
        q->items = dest;
    }

    q->items[q->last] = x;
    q->last = q->last + 1;
    q->count = q->count + 1;
}

int dequeue(queue *q)
{
    int x = q->items[q->first];
    q->first = (q->first + 1);
    q->count = q->count - 1;
    return (x);
}

int is_empty_queue(queue *q)
{
    return (q->count <= 0);
}

int has_next(queue *q)
{
    return q->iterator != q->last;
}

int next(queue *q)
{
    return q->items[q->iterator++];
}

char dict[MAX_NUMBER_OF_WORDS][MAX_LENGTH_OF_WORD + 1];
int word_cnt_by_len[MAX_LENGTH_OF_WORD];
char *p_subdict[MAX_LENGTH_OF_WORD][MAX_NUMBER_OF_WORDS + 1];
char *adjacency[MAX_LENGTH_OF_WORD][MAX_NUMBER_OF_WORDS];
int solution[MAX_NUMBER_OF_WORDS];
int discovered[MAX_NUMBER_OF_WORDS];
queue *q;

clock_t ts, te;

int readline(char *s)
{
    char c;
    int l = 0;

    while ((c = getchar()) != '\n')
    {
        *s = c;
        s++;
        l++;
    }

    *s = '\0';

    return l;
}

int is_doublet(const char *s, const char *t)
{
    int d = 0;

    while (*s)
    {
        if (*s != *t)
        {
            d++;

            if (d > 1)
            {
                return 0;
            }
        }

        s++;
        t++;
    }

    return d == 1;
}

int search(const char *key, int l)
{
    int i, w;

    w = word_cnt_by_len[l];
    p_subdict[l][w] = key;

    i = -1;
    do
    {
        i++;
    } while (strcmp(key, p_subdict[l][i]) != 0);

    return i < w ? i : -1;
}

int find_path(int l, int start, int end)
{
    int w = word_cnt_by_len[l];

    int i, v;

    init_queue(q);

    i = sizeof(int) * w;
    memset(discovered, 0, i);
    memset(solution, 255, i);

    enqueue(q, start);
    discovered[start] = 1;

    while (!is_empty_queue(q))
    {
        v = dequeue(q);

        if (adjacency[l][v] == NULL)
        {
            adjacency[l][v] = (char *)malloc(w);
            memset(adjacency[l][v], 'X', w);
        }

        for (i = 0; i < w; i++)
        {
            if (i != v)
            {
                if (*(adjacency[l][v] + i) == 'X')
                {
                    *(adjacency[l][v] + i) = is_doublet(p_subdict[l][v], p_subdict[l][i]);

                    if (adjacency[l][i] == NULL)
                    {
                        adjacency[l][i] = (char *)malloc(w);
                        memset(adjacency[l][i], 'X', w);
                    }

                    *(adjacency[l][i] + v) = *(adjacency[l][v] + i);
                }

                if (*(adjacency[l][v] + i) == 1)
                {
                    if (i == end)
                    {
                        solution[end] = v;
                        return 1;
                    }

                    if (!discovered[i])
                    {
                        enqueue(q, i);
                        discovered[i] = 1;
                        solution[i] = v;
                    }
                }
            }
        }
    }

    return 0;
}

int main(void)
{
    ts = clock();

    char buff[BUFFER_LENGTH];
    char word1[BUFFER_LENGTH];
    char word2[BUFFER_LENGTH];

    int build_graph[MAX_LENGTH_OF_WORD];

    int cases;
    int i, j, l, w;
    int start, end;

    stack s;

    q = create_queue(MAX_NUMBER_OF_WORDS);

    memset(word_cnt_by_len, 0, sizeof(word_cnt_by_len));
    memset(build_graph, 0, sizeof(build_graph));

    i = 0;
    while ((l = readline(dict[i])))
    {
        l--;
        j = word_cnt_by_len[l];
        p_subdict[l][j] = dict[i];
        word_cnt_by_len[l] = j + 1;
        i++;
    }

    cases = 0;
    while (scanf("%s %s", word1, word2) != EOF)
    {
        if (cases)
        {
            putchar('\n');
        }

        cases++;

        l = strlen(word1);
        if (l != strlen(word2))
        {
            puts("No solution.");
            continue;
        }

        l--;
        if (word_cnt_by_len[l] < 2)
        {
            puts("No solution.");
            continue;
        }

        start = search(word1, l);
        if (start < 0)
        {
            puts("No solution.");
            continue;
        }

        end = search(word2, l);
        if (end < 0)
        {
            puts("No solution.");
            continue;
        }

        if (l == 0)
        {
            puts(word1);
            puts(word2);
            continue;
        }

        if (!build_graph[l])
        {
            build_graph[l] = 1;

            w = word_cnt_by_len[l];
            for (i = 0; i < w; i++)
            {
                adjacency[l][i] = NULL;
            }
        }

        i = find_path(l, start, end);

        if (i)
        {
            init_stack(&s);

            j = end;
            push(&s, j);

            while ((j = solution[j]) >= 0)
            {
                push(&s, j);
            }

            while (!is_empty_stack(&s))
            {
                j = pop(&s);
                puts(p_subdict[l][j]);
            }
        }
        else
        {
            puts("No solution.");
        }
    }

    te = clock();
    printf("\nElapsed: %ld\n", te - ts);

    return EXIT_SUCCESS;
}
