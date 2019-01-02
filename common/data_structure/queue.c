#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned capacity;
  int *items; /* body of queue */
  int head;   /* position of head element */
  int tail;   /* position of tail element */
  int size;   /* number of queue elements */
} queue_t;

/* function to create a queue of given capacity. */
queue_t *create_queue(unsigned capacity) {
  queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
  if (!queue) {
    fprintf(stderr, "Error: Out of space!!! Exiting...\n");
    exit(EXIT_FAILURE);
  }

  queue->capacity = capacity;
  queue->size = 0, queue->head = 0, queue->tail = 0;
  queue->items = (int *)malloc(queue->capacity * sizeof(int));
  if (!queue->items) {
    fprintf(stderr, "Error: Out of space!!! Exiting...\n");
    exit(EXIT_FAILURE);
  }

  return queue;
}

/* function to free a queue. */
void free_queue(queue_t *queue) {
  if (queue) {
    if (queue->items) {
      free(queue->items);
      queue->items = NULL;
    }

    free(queue);
    queue = NULL;
  }
}

/* queue is full when size is equal to the capacity */
int is_full(queue_t *queue) { return queue->size == queue->capacity; }

/* queue is empty when size is equal to 0 */
int is_empty(queue_t *queue) { return queue->size == 0; }

void en_queue(queue_t *queue, int x) {
  if (is_full(queue)) {
    puts("Warning: queue overflow enqueue!!!");
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
    puts("Warning: empty queue dequeue!!!");
    return INT_MIN;
  }

  x = queue->items[queue->head++];
  if (queue->head == queue->capacity) {
    queue->head = 0;
  }
  queue->size--;

  return (x);
}

/* Driver program to test above functions */
int main() {
  queue_t *queue = create_queue(5);

  en_queue(queue, 10);
  en_queue(queue, 20);
  en_queue(queue, 30);
  en_queue(queue, 40);
  en_queue(queue, 50);
  en_queue(queue, 60);

  printf("%d de_queue\n", de_queue(queue));
  printf("%d de_queue\n", de_queue(queue));
  printf("%d de_queue\n", de_queue(queue));
  printf("%d de_queue\n", de_queue(queue));
  printf("%d de_queue\n", de_queue(queue));

  en_queue(queue, 70);
  en_queue(queue, 80);
  en_queue(queue, 90);
  en_queue(queue, 100);

  printf("%d de_queue\n", de_queue(queue));
  printf("%d de_queue\n", de_queue(queue));
  printf("%d de_queue\n", de_queue(queue));
  printf("%d de_queue\n", de_queue(queue));
  printf("%d de_queue\n", de_queue(queue));
  printf("%d de_queue\n", de_queue(queue));
  printf("%d de_queue\n", de_queue(queue));
  printf("%d de_queue\n", de_queue(queue));
  printf("%d de_queue\n", de_queue(queue));
  printf("%d de_queue\n", de_queue(queue));

  en_queue(queue, 100);
  printf("%d de_queue\n", de_queue(queue));

  return 0;
}