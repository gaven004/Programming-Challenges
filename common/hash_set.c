#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_INITIAL_CAPACITY (16) /* MUST be a power of two. */
#define MAXIMUM_CAPACITY (1073741824) /* MUST be a power of two <= 1<<30. */
#define DEFAULT_LOAD_FACTOR (0.75F)

typedef struct _hash_set_node {
  int hash;
  char *element;
  struct _hash_set_node *next;
} hash_set_node_t;

typedef struct {
  int size;          /* The number of elements contained in this set. */
  int table_size;    /* The size of table */
  int threshold;     /* The next size value at which to resize (capacity * load
                        factor). */
  float load_factor; /* The load factor for the hash set. */
  int (*hash)(const void *);
  int (*cmp)(const void *, const void *);
  hash_set_node_t **table;
} hash_set_t;

int _table_size_for(int cap);

void _add_set_node_internal(hash_set_t *set, hash_set_node_t *node);

hash_set_t *create_set(int capacity, float load_factor,
                       int (*hash)(const void *),
                       int (*cmp)(const void *, const void *));

void free_set(hash_set_t *set);

int add_set_node(hash_set_t *set, const char *element);

int remove_set_node(hash_set_t *set, const char *element);

int contains_set_node(hash_set_t *set, const char *element);

hash_set_t *union_set(hash_set_t *s, hash_set_t *t);

hash_set_t *intersection_set(hash_set_t *s, hash_set_t *t);

hash_set_t *resize_set(hash_set_t *set, int capacity);

void clear_set(hash_set_t *set);

void print_set(hash_set_t *set);

/*
 * Returns a power of two size for the given target capacity.
 */
int _table_size_for(int cap) {
  int n = cap - 1;
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  n |= n >> 16;
  return (n < 0) ? 1 : (n >= MAXIMUM_CAPACITY) ? MAXIMUM_CAPACITY : n + 1;
}

int strhash(char *s) {
  int h = 0;

  while (*s) {
    h = 31 * h + *s;
    s++;
  }

  return h;
}

hash_set_t *create_set(int capacity, float load_factor,
                       int (*hash)(const void *),
                       int (*cmp)(const void *, const void *)) {
  int i;

  if (capacity < 0)
    capacity = DEFAULT_INITIAL_CAPACITY;
  if (capacity > MAXIMUM_CAPACITY)
    capacity = MAXIMUM_CAPACITY;
  if (load_factor <= 0)
    load_factor = DEFAULT_LOAD_FACTOR;

  hash_set_t *set = (hash_set_t *)malloc(sizeof(hash_set_t));
  if (NULL == set) {
    fprintf(stderr, "Error: Out of space!!! Exiting...\n");
    exit(EXIT_FAILURE);
  }

  set->size = 0;
  set->load_factor = load_factor;
  set->table_size = _table_size_for(capacity);
  set->threshold = set->table_size * load_factor;
  set->hash = hash;
  set->cmp = cmp;

  set->table =
      (hash_set_node_t **)malloc(set->table_size * sizeof(hash_set_node_t *));
  if (NULL == set->table) {
    fprintf(stderr, "Error: Out of space!!! Exiting...\n");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < set->table_size; i++) {
    set->table[i] = NULL;
  }

  return set;
}

void free_set(hash_set_t *set) {
  clear_set(set);

  if (NULL != set->table) {
    free(set->table);
    set->table = NULL;
  }

  free(set);
  set = NULL;
}

void clear_set(hash_set_t *set) {
  int i;
  hash_set_node_t *current, *previous;

  for (i = 0; i < set->table_size; ++i) {
    current = set->table[i];

    while (current != NULL) {
      previous = current, current = current->next;
      free(previous);
    }

    set->table[i] = NULL;
  }

  set->size = 0;
}

void _add_set_node_internal(hash_set_t *set, hash_set_node_t *node) {
  int index;
  hash_set_node_t *current, *previous;

  index = node->hash % set->table_size;

  previous = NULL, current = set->table[index];
  while (current != NULL) {
    previous = current, current = current->next;
  }

  if (NULL == previous) {
    set->table[index] = node;
  } else {
    previous->next = node;
  }

  set->size++;
}

hash_set_t *resize_set(hash_set_t *set, int capacity) {
  int i;
  hash_set_node_t *node, *next;
  hash_set_t *new_set, *swap;

  new_set = create_set(capacity, set->load_factor, set->hash, set->cmp);

  for (i = 0; i < set->table_size; ++i) {
    node = set->table[i];
    while (node != NULL) {
      next = node->next, node->next = NULL;
      _add_set_node_internal(new_set, node);
      node = next;
    }
    set->table[i] = NULL;
  }

  free(set->table);

  set->size = new_set->size;
  set->load_factor = new_set->load_factor;
  set->table_size = new_set->table_size;
  set->threshold = new_set->threshold;
  set->table = new_set->table;

  free(new_set);

  return set;
}

void print_set(hash_set_t *set) {
  int i;
  hash_set_node_t *node;

  printf("set: [");
  for (i = 0; i < set->table_size; ++i) {
    node = set->table[i];
    while (node != NULL) {
      printf("%s;", node->element);
      node = node->next;
    }
  }
  printf("]\n");
}

int add_set_node(hash_set_t *set, const char *element) {
  int hash, index, len;
  hash_set_node_t *current, *previous;

  hash = set->hash(element);
  index = hash % set->table_size;

  previous = NULL;
  current = set->table[index];

  while (current != NULL) {
    if (current->hash == hash && set->cmp(element, current->element) == 0) {
      return 0;
    }
    previous = current;
    current = current->next;
  }

  current = (hash_set_node_t *)malloc(sizeof(hash_set_node_t));
  if (NULL == current) {
    fprintf(stderr, "Error: Out of space!!! Exiting...\n");
    exit(EXIT_FAILURE);
  }

  len = strlen(element);
  current->element = malloc((len + 1) * sizeof(char));
  if (NULL == current->element) {
    fprintf(stderr, "Error: Out of space!!! Exiting...\n");
    exit(EXIT_FAILURE);
  }
  strcpy(current->element, element);
  current->hash = hash;
  current->next = NULL;

  if (NULL == previous) {
    set->table[index] = current;
  } else {
    previous->next = current;
  }

  set->size++;
  if (set->size > set->threshold) {
    set = resize_set(set, set->table_size << 1);
  }

  return 1;
}

int remove_set_node(hash_set_t *set, const char *element) {
  int hash, index;
  hash_set_node_t *current, *previous;

  hash = set->hash(element);
  index = hash % set->table_size;
  current = set->table[index];
  previous = NULL;

  while (current != NULL) {
    if (current->hash == hash && set->cmp(element, current->element) == 0) {
      if (NULL == previous) {
        set->table[index] = NULL;
      } else {
        previous->next = current->next;
      }
      free(current);
      set->size--;
      return 1;
    }
    previous = current;
    current = current->next;
  }

  return 0;
}

int contains_set_node(hash_set_t *set, const char *element) {
  int hash, index;
  hash_set_node_t *node;

  hash = set->hash(element);
  index = hash % set->table_size;
  node = set->table[index];

  while (node != NULL) {
    if (node->hash == hash && set->cmp(element, node->element) == 0) {
      return 1;
    }
    node = node->next;
  }

  return 0;
}

hash_set_t *union_set(hash_set_t *s, hash_set_t *t) {
  int i;
  hash_set_node_t *node;

  for (i = 0; i < t->table_size; ++i) {
    node = t->table[i];
    while (node != NULL) {
      add_set_node(s, node->element);
      node = node->next;
    }
  }

  return s;
}

hash_set_t *intersection_set(hash_set_t *s, hash_set_t *t) {
  int i;
  hash_set_node_t *node;

  for (i = 0; i < s->table_size; ++i) {
    node = s->table[i];
    while (node != NULL) {
      if (!contains_set_node(t, node->element)) {
        remove_set_node(s, node->element);
      }
      node = node->next;
    }
  }

  return s;
}

int main() {
  hash_set_t *set = create_set(DEFAULT_INITIAL_CAPACITY, DEFAULT_LOAD_FACTOR,
                               (int (*)(const void *))strhash,
                               (int (*)(const void *, const void *))strcmp);
  add_set_node(set, "a");
  add_set_node(set, "b");
  add_set_node(set, "c");
  add_set_node(set, "d");
  add_set_node(set, "e");
  add_set_node(set, "f");
  add_set_node(set, "g");
  add_set_node(set, "h");
  add_set_node(set, "i");
  add_set_node(set, "a");
  add_set_node(set, "b");
  add_set_node(set, "c");
  add_set_node(set, "d");
  add_set_node(set, "e");
  add_set_node(set, "f");
  add_set_node(set, "g");
  add_set_node(set, "h");
  add_set_node(set, "i");
  print_set(set);

  remove_set_node(set, "a");
  remove_set_node(set, "b");
  remove_set_node(set, "c");
  print_set(set);

  clear_set(set);
  print_set(set);

  add_set_node(set, "a");
  add_set_node(set, "b");
  add_set_node(set, "c");
  add_set_node(set, "d");
  add_set_node(set, "e");
  add_set_node(set, "f");
  add_set_node(set, "g");
  add_set_node(set, "h");
  add_set_node(set, "i");
  add_set_node(set, "j");
  add_set_node(set, "k");
  add_set_node(set, "l");
  add_set_node(set, "m");
  add_set_node(set, "n");
  add_set_node(set, "o");
  add_set_node(set, "p");
  add_set_node(set, "q");
  add_set_node(set, "r");
  add_set_node(set, "s");
  add_set_node(set, "t");
  add_set_node(set, "u");
  add_set_node(set, "v");
  add_set_node(set, "w");
  add_set_node(set, "x");
  add_set_node(set, "y");
  add_set_node(set, "z");
  print_set(set);

  hash_set_t *t = create_set(DEFAULT_INITIAL_CAPACITY, DEFAULT_LOAD_FACTOR,
                             (int (*)(const void *))strhash,
                             (int (*)(const void *, const void *))strcmp);
  add_set_node(t, "a");
  add_set_node(t, "b");
  add_set_node(t, "c");
  add_set_node(t, "d");
  add_set_node(t, "e");
  add_set_node(t, "f");
  add_set_node(t, "g");
  add_set_node(t, "h");
  add_set_node(t, "i");
  add_set_node(t, "a");
  add_set_node(t, "b");
  add_set_node(t, "c");
  add_set_node(t, "d");
  add_set_node(t, "e");
  add_set_node(t, "f");
  add_set_node(t, "g");
  add_set_node(t, "h");
  add_set_node(t, "i");
  print_set(t);

  union_set(set, t);
  print_set(set);

  intersection_set(set, t);
  print_set(set);
}