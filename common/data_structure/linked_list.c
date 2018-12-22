#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
  int element;
  struct _node *next;
} node_t, list_t;

list_t *create_list() {
  list_t *list = (list_t *)malloc(sizeof(list_t));
  if (NULL == list) {
    fprintf(stderr, "Error: Out of space!!! Exiting...\n");
    exit(EXIT_FAILURE);
  }

  list->next = NULL;
  return list;
}

void clear_list(list_t *list) {
  node_t *current, *next;

  current = list->next;
  while (NULL != current) {
    next = current->next;
    free(current);
    current = next;
  }

  list->next = NULL;
}

void free_list(list_t *list) {
  clear_list(list);
  free(list);
}

int is_empty(list_t *list) { return (list->next == NULL); }

void insert_beginning(list_t *list, int x) {
  node_t *node = (node_t *)malloc(sizeof(node_t));
  if (NULL == node) {
    fprintf(stderr, "Error: Out of space!!! Exiting...\n");
    exit(EXIT_FAILURE);
  }

  node->element = x;
  node->next = list->next;
  list->next = node;
}

void remove_beginning(list_t *list) {
  node_t *node = list->next;
  if (NULL != node) {
    list->next = node->next;
    free(node);
  }
}

void insert_last(list_t *list, int x) {
  node_t *node, *current;

  node = (node_t *)malloc(sizeof(node_t));
  if (NULL == node) {
    fprintf(stderr, "Error: Out of space!!! Exiting...\n");
    exit(EXIT_FAILURE);
  }

  node->element = x;
  node->next = NULL;

  current = list;
  while (NULL != current->next) {
    current = current->next;
  }

  current->next = node;
}

void remove_last(list_t *list) {
  node_t *current, *previous;

  previous = list, current = list->next;
  if (NULL != current) {
    while (NULL != current->next) {
      previous = current, current = current->next;
    }

    free(current);
    previous->next = NULL;
  }
}

void print_list(list_t *list) {
  node_t *node;

  printf("List: ");
  for (node = list->next; NULL != node; node = node->next) {
    printf("%d ", node->element);
  }
  putchar('\n');
}

int main() {
  list_t *list = create_list();
  insert_beginning(list, 10);
  insert_beginning(list, 20);
  insert_beginning(list, 30);
  insert_last(list, 40);
  insert_last(list, 50);
  insert_last(list, 60);
  print_list(list);

  remove_beginning(list);
  remove_last(list);
  remove_last(list);
  print_list(list);

  insert_beginning(list, 70);
  insert_beginning(list, 80);
  insert_last(list, 90);
  insert_last(list, 100);
  print_list(list);

  clear_list(list);
  print_list(list);

  remove_beginning(list);
  remove_last(list);
  remove_last(list);
  print_list(list);

  insert_beginning(list, 70);
  insert_beginning(list, 80);
  insert_last(list, 90);
  insert_last(list, 100);
  print_list(list);
}