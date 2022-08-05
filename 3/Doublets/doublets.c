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

typedef struct _node
{
    int element;
    struct _node *next;
} node;

typedef struct
{
    struct _node *head;
    struct _node *tail;
} adj_info;

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

int is_empty_queue(queue *q)
{
    if (q->count <= 0)
        return (1);
    else
        return (0);
}

char dict[MAX_NUMBER_OF_WORDS][MAX_LENGTH_OF_WORD + 1];
int word_cnt_by_len[MAX_LENGTH_OF_WORD];
char *p_subdict[MAX_LENGTH_OF_WORD][MAX_NUMBER_OF_WORDS];
adj_info adjacency[MAX_LENGTH_OF_WORD][MAX_NUMBER_OF_WORDS];
int solution[MAX_NUMBER_OF_WORDS];

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

    while (*s && *t)
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

void add_adjacency(int l, int i, int j)
{
    node *ni = (node *)malloc(sizeof(node));
    node *nj = (node *)malloc(sizeof(node));

    ni->element = j;
    ni->next = NULL;

    nj->element = i;
    nj->next = NULL;

    if (adjacency[l][i].tail == NULL)
    {
        adjacency[l][i].head = ni;
        adjacency[l][i].tail = ni;
    }
    else
    {
        adjacency[l][i].tail->next = ni;
        adjacency[l][i].tail = ni;
    }

    if (adjacency[l][j].tail == NULL)
    {
        adjacency[l][j].head = nj;
        adjacency[l][j].tail = nj;
    }
    else
    {
        adjacency[l][j].tail->next = nj;
        adjacency[l][j].tail = nj;
    }
}

int search(const char *key, int l)
{
    int i, w;

    w = word_cnt_by_len[l];
    for (i = 0; i < w; i++)
    {
        if (strcmp(key, p_subdict[l][i]) == 0)
        {
            return i;
        }
    }

    return -1;
}

int find_path(int l, int start, int end)
{
    int w = word_cnt_by_len[l];
    int discovered[w];

    int i, v;

    queue q;
    init_queue(&q);

    for (i = 0; i < w; i++)
    {
        discovered[i] = 0;
        solution[i] = -1;
    }

    enqueue(&q, start);
    discovered[start] = 1;

    while (!is_empty_queue(&q))
    {
        v = dequeue(&q);

        adj_info ai = adjacency[l][v];
        node *current = ai.head;

        while (current != NULL)
        {
            if (current->element == end)
            {
                solution[end] = v;
                return 1;
            }

            if (!discovered[current->element])
            {
                enqueue(&q, current->element);
                discovered[current->element] = 1;
                solution[current->element] = v;
            }

            current = current->next;
        }
    }

    return 0;
}

int main(void)
{
    char buff[BUFFER_LENGTH];
    char word1[BUFFER_LENGTH];
    char word2[BUFFER_LENGTH];

    int cases;
    int i, j, l, w;
    int start, end;

    stack s;

    for (i = 0; i < MAX_LENGTH_OF_WORD; i++)
    {
        word_cnt_by_len[i] = 0;
    }

    i = 0;
    while ((l = readline(dict[i])))
    {
        l--;
        j = word_cnt_by_len[l];
        p_subdict[l][j] = dict[i];
        word_cnt_by_len[l] = j + 1;
        i++;
    }

    for (l = 0; l < MAX_LENGTH_OF_WORD; l++)
    {
        w = word_cnt_by_len[l];
        if (w > 1)
        {
            /* qsort(p_subdict[l], w, sizeof(char *), (int (*)(const void *, const void *))strcmp); */

            for (i = 0; i < w; i++)
            {
                adjacency[l][i].head = NULL;
                adjacency[l][i].tail = NULL;
            }

            for (i = 0; i < w - 1; i++)
            {
                for (j = i + 1; j < w; j++)
                {
                    if (is_doublet(p_subdict[l][i], p_subdict[l][j]))
                    {
                        add_adjacency(l, i, j);
                    }
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
        if (word_cnt_by_len[l] < 2)
        {
            puts("No solution.");
            continue;
        }

        start = search(word1, l);
        end = search(word2, l);

        if (start < 0 || end < 0)
        {
            puts("No solution.");
            continue;
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

    return EXIT_SUCCESS;
}
