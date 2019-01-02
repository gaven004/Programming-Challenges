#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_INITIAL_CAPACITY (16) /* MUST be a power of two. */
#define MAXIMUM_CAPACITY (1073741824) /* MUST be a power of two <= 1<<30. */
#define DEFAULT_LOAD_FACTOR (0.75F)

typedef struct _hash_map_node {
  int hash;
  char *key;
  char *value;
  struct _hash_map_node *next;
} hash_map_node_t;

typedef struct {
  int size;       /* The number of key-value mappings contained in this map. */
  int table_size; /* The size of table */
  int threshold;  /* The next size value at which to resize (capacity * load
                     factor). */
  float load_factor; /* The load factor for the hash table. */
  hash_map_node_t **table;
} hash_map_t;

int _table_size_for(int cap);
void _set_node(hash_map_node_t *node, char *key, char *value);
void _put_map_node_internal(hash_map_t *map, hash_map_node_t *node);
int strhash(char *s);
hash_map_t *create_map(int capacity, float load_factor);
hash_map_t *create_map_default();
void clear_map(hash_map_t *map);
void free_map(hash_map_t *map);
void put_map_node(hash_map_t *map, char *key, char *value);
char *get_map_node(hash_map_t *map, char *key);
void delete_map_node(hash_map_t *map, char *key);
int contains_map_key(hash_map_t *map, char *key);
hash_map_t *resize_map(hash_map_t *map, int capacity);
void print_map(hash_map_t *map);

int main() {
  int hash, capacity;
  char *str = "Hello World!!";
  printf("Hash of '%s': %d\n", str, hash);

  capacity = 100;
  printf("_table_size_for %d: %d\n", capacity, _table_size_for(capacity));
  capacity = 1000;
  printf("_table_size_for %d: %d\n", capacity, _table_size_for(capacity));
  capacity = 10000;
  printf("_table_size_for %d: %d\n", capacity, _table_size_for(capacity));
  capacity = DEFAULT_INITIAL_CAPACITY;
  printf("_table_size_for %d: %d\n", capacity, _table_size_for(capacity));
  capacity = MAXIMUM_CAPACITY;
  printf("_table_size_for %d: %d\n", capacity, _table_size_for(capacity));

  hash_map_t *map = create_map_default();
  put_map_node(map, "a", "1");
  put_map_node(map, "b", "2");
  put_map_node(map, "c", "3");
  put_map_node(map, "d", "4");
  put_map_node(map, "e", "5");
  print_map(map);

  put_map_node(map, "b", "b2");
  put_map_node(map, "c", "c3");
  print_map(map);

  printf("get key: %s -> %s\n", "a", get_map_node(map, "a"));
  printf("get key: %s -> %s\n", "b", get_map_node(map, "b"));
  printf("get key: %s -> %s\n", "c", get_map_node(map, "c"));
  printf("get key: %s -> %s\n", "f", get_map_node(map, "f"));

  delete_map_node(map, "a");
  delete_map_node(map, "d");
  print_map(map);

  clear_map(map);
  print_map(map);

  put_map_node(map, "a", "1");
  put_map_node(map, "b", "2");
  put_map_node(map, "c", "3");
  put_map_node(map, "d", "4");
  put_map_node(map, "e", "5");
  put_map_node(map, "f", "6");
  put_map_node(map, "g", "7");
  put_map_node(map, "h", "8");
  put_map_node(map, "i", "9");
  put_map_node(map, "j", "10");
  put_map_node(map, "k", "11");
  put_map_node(map, "l", "12");
  put_map_node(map, "m", "13");
  put_map_node(map, "n", "14");
  put_map_node(map, "o", "15");
  put_map_node(map, "p", "16");
  put_map_node(map, "q", "17");
  put_map_node(map, "r", "18");
  put_map_node(map, "s", "19");
  put_map_node(map, "t", "10");
  put_map_node(map, "u", "21");
  put_map_node(map, "v", "22");
  put_map_node(map, "w", "23");
  put_map_node(map, "x", "24");
  put_map_node(map, "y", "25");
  put_map_node(map, "z", "26");
  print_map(map);
}

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

hash_map_t *create_map(int capacity, float load_factor) {
  int i;

  if (capacity < 0)
    capacity = DEFAULT_INITIAL_CAPACITY;
  if (capacity > MAXIMUM_CAPACITY)
    capacity = MAXIMUM_CAPACITY;
  if (load_factor <= 0)
    load_factor = DEFAULT_LOAD_FACTOR;

  hash_map_t *map = (hash_map_t *)malloc(sizeof(hash_map_t));
  if (!map) {
    fprintf(stderr, "Error: Out of space!!! Exiting...\n");
    exit(EXIT_FAILURE);
  }

  map->size = 0;
  map->load_factor = load_factor;
  map->table_size = _table_size_for(capacity);
  map->threshold = map->table_size * load_factor;

  map->table =
      (hash_map_node_t **)malloc(map->table_size * sizeof(hash_map_node_t *));
  if (!map->table) {
    fprintf(stderr, "Error: Out of space!!! Exiting...\n");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < map->table_size; i++) {
    map->table[i] = NULL;
  }

  return map;
}

hash_map_t *create_map_default() {
  return create_map(DEFAULT_INITIAL_CAPACITY, DEFAULT_LOAD_FACTOR);
}

/**
 * Removes all of the mappings from this map.
 */
void clear_map(hash_map_t *map) {
  int i;
  hash_map_node_t *node, *previous;

  for (i = 0; i < map->table_size; ++i) {
    node = map->table[i];

    while (node) {
      previous = node, node = node->next;
      free(previous);
    }

    map->table[i] = NULL;
  }

  map->size = 0;
}

void free_map(hash_map_t *map) {
  clear_map(map);

  if (map->table) {
    free(map->table);
    map->table = NULL;
  }

  free(map);
  map = NULL;
}

void _set_node(hash_map_node_t *node, char *key, char *value) {
  int len;
  char *pnew;

  if (key) {
    len = strlen(key);
    pnew = malloc((len + 1) * sizeof(char));
    if (!pnew) {
      fprintf(stderr, "Error: Out of space!!! Exiting...\n");
      exit(EXIT_FAILURE);
    }
    strcpy(pnew, key);
    free(node->key);
    node->key = pnew;
  }

  len = strlen(value);
  pnew = malloc((len + 1) * sizeof(char));
  if (!pnew) {
    fprintf(stderr, "Error: Out of space!!! Exiting...\n");
    exit(EXIT_FAILURE);
  }
  strcpy(pnew, value);
  if (node->value) {
    free(node->value);
  }
  node->value = pnew;
}

void put_map_node(hash_map_t *map, char *key, char *value) {
  int hash, index;
  hash_map_node_t *node;

  hash = strhash(key);
  index = (hash & 0x7FFFFFFF) % map->table_size;
  node = map->table[index];
  while (node) {
    if (node->hash == hash && !strcmp(key, node->key)) {
      if (strcmp(value, node->value)) {
        _set_node(node, NULL, value);
      }
      return;
    }
    node = node->next;
  }

  node = (hash_map_node_t *)malloc(sizeof(hash_map_node_t));
  if (!node) {
    fprintf(stderr, "Error: Out of space!!! Exiting...\n");
    exit(EXIT_FAILURE);
  }

  node->hash = hash;
  node->key = NULL;
  node->value = NULL;
  _set_node(node, key, value);
  node->next = map->table[index];

  map->table[index] = node;
  map->size++;
  if (map->size > map->threshold) {
    map = resize_map(map, map->table_size << 1);
  }
}

char *get_map_node(hash_map_t *map, char *key) {
  int hash, index;
  hash_map_node_t *node;

  hash = strhash(key);
  index = (hash & 0x7FFFFFFF) % map->table_size;
  node = map->table[index];

  while (node) {
    if (node->hash == hash && strcmp(key, node->key) == 0) {
      return node->value;
    }
    node = node->next;
  }

  return NULL;
}

void delete_map_node(hash_map_t *map, char *key) {
  int hash, index;
  hash_map_node_t *current, *previous;

  hash = strhash(key);
  index = (hash & 0x7FFFFFFF) % map->table_size;
  current = map->table[index];
  previous = NULL;

  while (current) {
    if (current->hash == hash && strcmp(key, current->key) == 0) {
      if (!previous) {
        map->table[index] = NULL;
      } else {
        previous->next = current->next;
      }
      free(current);
      map->size--;
      return;
    }
    previous = current;
    current = current->next;
  }
}

int contains_map_key(hash_map_t *map, char *key) {
  int hash, index;
  hash_map_node_t *node;

  hash = strhash(key);
  index = (hash & 0x7FFFFFFF) % map->table_size;
  node = map->table[index];

  while (node) {
    if (node->hash == hash && strcmp(key, node->key) == 0) {
      return 1;
    }
    node = node->next;
  }

  return 0;
}

void _put_map_node_internal(hash_map_t *map, hash_map_node_t *node) {
  int index;

  index = (node->hash & 0x7FFFFFFF) % map->table_size;
  node->next = map->table[index];
  map->table[index] = node;
  map->size++;
}

hash_map_t *resize_map(hash_map_t *map, int capacity) {
  int i;
  hash_map_node_t *current, *next;
  hash_map_t *new_map, *swap;

  new_map = create_map(capacity, map->load_factor);

  for (i = 0; i < map->table_size; ++i) {
    current = map->table[i];
    while (current) {
      next = current->next, current->next = NULL;
      _put_map_node_internal(new_map, current);
      current = next;
    }
    map->table[i] = NULL;
  }

  free(map->table);

  map->size = new_map->size;
  map->load_factor = new_map->load_factor;
  map->table_size = new_map->table_size;
  map->threshold = new_map->threshold;
  map->table = new_map->table;

  free(new_map);
  return map;
}

void print_map(hash_map_t *map) {
  int i;
  hash_map_node_t *node;

  printf("map: [");
  for (i = 0; i < map->table_size; ++i) {
    node = map->table[i];
    while (node) {
      printf("%s->%s;", node->key, node->value);
      node = node->next;
    }
  }
  printf("]\n");
}