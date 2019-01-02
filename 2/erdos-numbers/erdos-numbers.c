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

typedef struct _hash_set_node {
  char value[MAX_LENGTH_OF_NAME];
  struct _hash_set_node *next;
} hash_set_node_t;

typedef struct {
  int table_size; /* The size of table */
  hash_set_node_t **table;
} hash_set_t;

typedef struct {
  char name[MAX_LENGTH_OF_NAME];
  int erdos_num;
  int visited;
  hash_set_t *coauthors;
} author_t;

typedef struct _hash_map_node {
  char key[MAX_LENGTH_OF_NAME];
  author_t *value;
  struct _hash_map_node *next;
} hash_map_node_t;

typedef struct {
  int table_size; /* The size of table */
  hash_map_node_t **table;
} hash_map_t;

typedef struct {
  unsigned capacity;
  author_t **items; /* body of queue */
  int head;         /* position of head element */
  int tail;         /* position of tail element */
  int size;         /* number of queue elements */
} queue_t;

hash_map_t *authors;
queue_t *queue;

int strhash(const char *s) {
  int h = 0;

  while (*s) {
    h = 31 * h + *s;
    s++;
  }

  return h;
}

/* Begin of queue */
queue_t *create_queue(unsigned capacity) {
  queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
  queue->capacity = capacity;
  queue->size = queue->head = queue->tail = 0;
  queue->items = (author_t **)malloc(queue->capacity * sizeof(author_t *));
  return queue;
}

void clear_queue(queue_t *queue) {
  queue->size = queue->head = queue->tail = 0;
}

int is_full(queue_t *queue) { return queue->size == queue->capacity; }

int is_empty(queue_t *queue) { return queue->size == 0; }

void en_queue(queue_t *queue, author_t *x) {
  if (is_full(queue)) {
    return;
  }

  queue->items[queue->tail++] = x;
  if (queue->tail == queue->capacity) {
    queue->tail = 0;
  }
  queue->size++;
}

author_t *de_queue(queue_t *queue) {
  author_t *x;

  if (is_empty(queue)) {
    return NULL;
  }

  x = queue->items[queue->head++];
  if (queue->head == queue->capacity) {
    queue->head = 0;
  }
  queue->size--;

  return (x);
}
/* End of queue */

/* Begin of hash set */
hash_set_t *create_set() {
  int i;

  hash_set_t *set = (hash_set_t *)malloc(sizeof(hash_set_t));
  set->table_size = 128;
  set->table =
      (hash_set_node_t **)malloc(set->table_size * sizeof(hash_set_node_t *));

  for (i = 0; i < set->table_size; i++) {
    set->table[i] = NULL;
  }

  return set;
}

int add_set_node(hash_set_t *set, const char *value) {
  int hash, index, len;
  hash_set_node_t *node;

  hash = strhash(value);
  index = (hash & 0x7FFFFFFF) % set->table_size;

  node = set->table[index];
  while (node) {
    if (!strcmp(node->value, value)) {
      return 0;
    }
    node = node->next;
  }

  node = (hash_set_node_t *)malloc(sizeof(hash_set_node_t));
  strcpy(node->value, value);
  node->next = set->table[index];

  set->table[index] = node;

  return 1;
}
/* End of hash set */

/* Begin of hash map */
hash_map_t *create_map() {
  int i;

  hash_map_t *map = (hash_map_t *)malloc(sizeof(hash_map_t));

  map->table_size = 16384;

  map->table =
      (hash_map_node_t **)malloc(map->table_size * sizeof(hash_map_node_t *));

  for (i = 0; i < map->table_size; i++) {
    map->table[i] = NULL;
  }

  return map;
}

void clear_map(hash_map_t *map) {
  int i;
  hash_map_node_t *node, *previous;

  for (i = 0; i < map->table_size; ++i) {
    node = map->table[i];

    while (node) {
      previous = node, node = node->next;
      free(previous->value->coauthors);
      free(previous->value);
      free(previous);
    }

    map->table[i] = NULL;
  }
}

author_t *put_map_node(hash_map_t *map, const char *key, const char *name) {
  int hash, index;
  hash_map_node_t *node;

  hash = strhash(key);
  index = (hash & 0x7FFFFFFF) % map->table_size;

  node = map->table[index];
  while (node) {
    if (!strcmp(key, node->key)) {
      return node->value;
    }
    node = node->next;
  }

  node = (hash_map_node_t *)malloc(sizeof(hash_map_node_t));
  strcpy(node->key, key);
  author_t *value = (author_t *)malloc(sizeof(author_t));
  strcpy(value->name, name);
  value->erdos_num = INT_MAX;
  value->visited = 0;
  value->coauthors = create_set();
  node->value = value;
  node->next = map->table[index];

  map->table[index] = node;

  return value;
}

author_t *get_map_value(hash_map_t *map, const char *key) {
  int hash, index;
  hash_map_node_t *node;

  hash = strhash(key);
  index = (hash & 0x7FFFFFFF) % map->table_size;
  node = map->table[index];

  while (node) {
    if (!strcmp(key, node->key)) {
      return node->value;
    }
    node = node->next;
  }

  return NULL;
}
/* End of map */

void add_authors(char *buff) {
  int f, i, j, n;
  char names[MAX_NUMBER_OF_AUTHORS][MAX_LENGTH_OF_NAME], *ps, *pt;
  author_t *author;

  n = f = 0, ps = buff, pt = names[n];
  while (*ps != ':') {
    if (*ps == ',') {
      if (f) {
        f = 0, *pt = '\0', n++;
        pt = names[n], ps += 2;
      } else {
        f = 1, *pt++ = *ps++;
      }
    } else {
      *pt++ = *ps++;
    }
  }

  *pt = '\0', n++;

  for (i = 0; i < n; i++) {
    author = put_map_node(authors, names[i], names[i]);

    for (j = 0; j < n; j++) {
      if (i != j) {
        add_set_node(author->coauthors, names[j]);
      }
    }
  }
}

void init_4_calc() {
  author_t *root;
  root = get_map_value(authors, "Erdos, P.");
  if (root) {
    root->erdos_num = 0;
    en_queue(queue, root);
  }
}

int get_distance(const char *key) {
  int i, v;
  author_t *current, *next;
  hash_set_t *coauthors;
  hash_set_node_t *coauthor;

  current = get_map_value(authors, key);

  if (!current) {
    return INT_MAX;
  }

  if (current->visited) {
    return current->erdos_num;
  }

  while (!is_empty(queue)) {
    current = de_queue(queue);

    coauthors = current->coauthors;

    if (coauthors) {
      for (i = 0; i < coauthors->table_size; i++) {
        coauthor = coauthors->table[i];
        while (coauthor) {
          next = get_map_value(authors, coauthor->value);

          if (!next->visited) {
            if (next->erdos_num > current->erdos_num + 1) {
              next->erdos_num = current->erdos_num + 1;
            }
            en_queue(queue, next);
          }

          coauthor = coauthor->next;
        }
      }
    }

    current->visited = 1;

    if (!strcmp(current->name, key)) {
      return current->erdos_num;
    }
  }

  return INT_MAX;
}

int main() {
  int scenarios, P, N, en;
  int s, i, j, k, v;
  char buff[BUFFER_LENGTH];

  for (scanf("%d", &scenarios), s = 1; s <= scenarios; s++) {
    authors = create_map();
    queue = create_queue(MAX_NUMBER_OF_AUTHORS * MAX_LINKS);

    scanf("%d %d", &P, &N), gets(buff);
    for (i = 0; i < P; i++) {
      gets(buff);
      add_authors(buff);
    }

    init_4_calc();

    printf("Scenario %d\n", s);
    for (i = 0; i < N; i++) {
      gets(buff);
      if ((v = get_distance(buff)) < INT_MAX) {
        printf("%s %d\n", buff, v);
      } else {
        printf("%s infinity\n", buff);
      }
    }
  }

  return 0;
}
