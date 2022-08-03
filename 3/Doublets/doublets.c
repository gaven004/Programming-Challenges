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
    int q[MAX_NUMBER_OF_WORDS + 1];
    int first;
    int last;
    int count;
} queue;

void init_queue(queue *q)
{
    q->first = 0;
    q->last = MAX_NUMBER_OF_WORDS - 1;
    q->count = 0;
}

void enqueue(queue *q, int x)
{
    if (q->count >= MAX_NUMBER_OF_WORDS)
        printf("Warning: queue overflow enqueue x=%d\n", x);
    else
    {
        q->last = (q->last + 1) % MAX_NUMBER_OF_WORDS;
        q->q[q->last] = x;
        q->count = q->count + 1;
    }
}

int dequeue(queue *q)
{
    int x;
    if (q->count <= 0)
    {
        printf("Warning: empty queue dequeue.\n");
    }
    else
    {
        x = q->q[q->first];
        q->first = (q->first + 1) % MAX_NUMBER_OF_WORDS;
        q->count = q->count - 1;
    }
    return (x);
}

int empty(queue *q)
{
    if (q->count <= 0)
        return (1);
    else
        return (0);
}

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

    while (*s && *t && d < 2)
    {
        if (*s != *t)
        {
            d++;
        }

        s++;
        t++;
    }

    return d == 1;
}

int search(const char *key,
           const char base[MAX_NUMBER_OF_WORDS][MAX_LENGTH_OF_WORD + 1],
           int num,
           int width)
{
    void *result = bsearch(key, base, num, width, (int (*)(const void *, const void *))strcmp);

    return result ? ((void *)result - (void *)base) / width : -1;
}

int find_path(char adjacency[MAX_LENGTH_OF_WORD][MAX_NUMBER_OF_WORDS], int start, int end, int width, int solution[MAX_NUMBER_OF_WORDS])
{
    int discovered[width];

    int i, v;

    queue q;
    init_queue(&q);

    for (i = 0; i < width; i++)
    {
        discovered[i] = 0;
        solution[i] = -1;
    }

    enqueue(&q, start);
    discovered[start] = 1;

    while (!empty(&q))
    {
        v = dequeue(&q);

        for (i = 0; i < width; i++)
        {
            if (adjacency[v][i])
            {
                if (i == end)
                {
                    solution[i] = v;
                    return 1;
                }

                if (!discovered[i])
                {
                    enqueue(&q, i);
                    discovered[i] = 1;
                    solution[i] = v;
                }
            }
        }
    }

    return 0;
}

char dict[MAX_LENGTH_OF_WORD][MAX_NUMBER_OF_WORDS][MAX_LENGTH_OF_WORD + 1];
int word_cnt_by_len[MAX_LENGTH_OF_WORD];
char adjacency[MAX_LENGTH_OF_WORD][MAX_LENGTH_OF_WORD][MAX_NUMBER_OF_WORDS];

int main(void)
{
    char buff[BUFFER_LENGTH];
    char word1[BUFFER_LENGTH];
    char word2[BUFFER_LENGTH];

    int cases;
    int i, j, l;
    int start, end;

    stack s;
    int solution[MAX_NUMBER_OF_WORDS];

    for (i = 0; i < MAX_LENGTH_OF_WORD; i++)
    {
        word_cnt_by_len[i] = 0;
    }

    while ((l = readline(buff)))
    {
        l--;
        i = word_cnt_by_len[l];
        strcpy(dict[l][i], buff);
        word_cnt_by_len[l] = i + 1;
    }

    for (l = 0; l < MAX_LENGTH_OF_WORD; l++)
    {
        if (word_cnt_by_len[l] > 1)
        {
            qsort(dict[l], word_cnt_by_len[l], MAX_LENGTH_OF_WORD + 1, (int (*)(const void *, const void *))strcmp);

            for (i = 0; i < word_cnt_by_len[l] - 1; i++)
            {
                for (j = i + 1; j < word_cnt_by_len[l]; j++)
                {
                    adjacency[l][i][j] = is_doublet(dict[l][i], dict[l][j]);
                    adjacency[l][j][i] = adjacency[l][i][j];
                }
            }
        }
    }

    cases = 0;
    while (scanf("%s", word1) != EOF && scanf("%s", word2) != EOF)
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
        start = search(word1, dict[l], word_cnt_by_len[l], MAX_LENGTH_OF_WORD + 1);
        end = search(word2, dict[l], word_cnt_by_len[l], MAX_LENGTH_OF_WORD + 1);

        if (start < 0 || end < 0)
        {
            puts("No solution.");
            continue;
        }

        i = find_path(adjacency[l], start, end, word_cnt_by_len[l], solution);
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
                puts(dict[l][j]);
            }
        }
        else
        {
            puts("No solution.");
        }
    }

    return EXIT_SUCCESS;
}
