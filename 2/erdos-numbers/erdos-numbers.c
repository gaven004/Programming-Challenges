/*
 * Erd¨os Numbers
 * PC/UVa IDs: 110206/10044
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NUMBER_OF_AUTHORS (10000)
#define MAX_LENGTH_OF_NAME (101)
#define BUFFER_LENGTH (10001)
#define MAX_LINKS (501)

typedef struct {
  unsigned capacity;
  int *items; /* body of queue */
  int head;   /* position of head element */
  int tail;   /* position of tail element */
  int size;   /* number of queue elements */
} queue_t;

int nAuthors;
char authors[MAX_NUMBER_OF_AUTHORS][MAX_LENGTH_OF_NAME];
int graph[MAX_NUMBER_OF_AUTHORS][MAX_NUMBER_OF_AUTHORS];
int distance[MAX_NUMBER_OF_AUTHORS], visited[MAX_NUMBER_OF_AUTHORS];
queue_t *queue;

queue_t *create_queue(unsigned capacity) {
  queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
  queue->capacity = capacity;
  queue->size = queue->head = queue->tail = 0;
  queue->items = (int *)malloc(queue->capacity * sizeof(int));
  return queue;
}

void clear_queue(queue_t *queue) {
  queue->size = queue->head = queue->tail = 0;
}

int is_full(queue_t *queue) { return queue->size == queue->capacity; }

int is_empty(queue_t *queue) { return queue->size == 0; }

void en_queue(queue_t *queue, int x) {
  if (is_full(queue)) {
    return;
  }

  queue->items[queue->tail++] = x;
  if (queue->tail == queue->capacity) {
    queue->tail = 0;
  }
  queue->size++;
}

int de_queue(queue_t *queue) {
  int x;

  if (is_empty(queue)) {
    return INT_MIN;
  }

  x = queue->items[queue->head++];
  if (queue->head == queue->capacity) {
    queue->head = 0;
  }
  queue->size--;

  return (x);
}

int index_of(const char *name) {
  int i;

  for (i = 0; i < nAuthors; i++) {
    if (!strcmp(authors[i], name)) {
      return i;
    }
  }

  return -1;
}

int put(const char *name) {
  int i;

  i = index_of(name);

  if (i >= 0) {
    return i;
  }

  strcpy(authors[nAuthors], name);

  return nAuthors++;
}

void add_authors(char *buff) {
  char name[MAX_LENGTH_OF_NAME], *ps, *pt;
  int f, i, j, k, n, a[MAX_NUMBER_OF_AUTHORS];

  ps = buff, pt = name, n = f = 0;
  while (*ps != ':') {
    if (*ps == ',') {
      if (f) {
        f = 0, *pt = '\0';
        k = put(name), a[n++] = k;
        pt = name, ps += 2;
      } else {
        f = 1, *pt++ = *ps++;
      }
    } else {
      *pt++ = *ps++;
    }
  }

  *pt = '\0', k = put(name), a[n++] = k;

  for (i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++) {
      graph[a[i]][a[j]] = graph[a[j]][a[i]] = 1;
    }
  }
}

void init_4_calc() {
  int i;

  distance[0] = 0, visited[0] = 0;
  for (i = 1; i < nAuthors; i++) {
    distance[i] = INT_MAX, visited[i] = 0;
  }
}

int get_distance(int k) {
  int i, v, current;

  if (visited[k]) {
    return distance[k];
  }

  while (!is_empty(queue)) {
    current = de_queue(queue);

    for (i = 0; i < nAuthors; i++) {
      if (graph[current][i] && !visited[i]) {
        if (distance[i] > distance[current] + 1) {
          distance[i] = distance[current] + 1;
        }
        en_queue(queue, i);
      }
    }

    visited[current] = 1;

    if (current == k) {
      return distance[k];
    }
  }
  return INT_MAX;
}

int main() {
  clock_t start, end;

  int scenarios, P, N, en;
  int s, i, j, k, v;
  char buff[BUFFER_LENGTH];

  start = clock();

  queue = create_queue(MAX_NUMBER_OF_AUTHORS * MAX_LINKS);
  strcpy(authors[0], "Erdos, P.");

  for (scanf("%d", &scenarios), s = 1; s <= scenarios; s++) {
    if (s > 1) {
      clear_queue(queue);
    }

    nAuthors = 1;

    for (i = 0; i < MAX_NUMBER_OF_AUTHORS; i++) {
      for (j = 0; j < MAX_NUMBER_OF_AUTHORS; j++) {
        graph[i][j] = 0;
      }
    }

    scanf("%d %d", &P, &N), gets(buff);
    for (i = 0; i < P; i++) {
      gets(buff);
      add_authors(buff);
    }

    init_4_calc();
    en_queue(queue, 0);

    printf("Scenario %d\n", s);
    for (i = 0; i < N; i++) {
      gets(buff);

      if ((k = index_of(buff)) >= 0 && (v = get_distance(k)) < INT_MAX) {
        printf("%s %d\n", buff, v);
      } else {
        printf("%s infinity\n", buff);
      }
    }
  }

  end = clock();
  printf("\nElapsed: %ld\n", end - start);

  return 0;
}
