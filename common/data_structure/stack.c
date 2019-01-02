#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int top;
  unsigned capacity;
  int *items;
} stack_t;

/* function to create a stack of given capacity. */
stack_t *create_stack(unsigned capacity) {
  stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
  if (!stack) {
    fprintf(stderr, "Error: Out of space!!! Exiting...\n");
    exit(EXIT_FAILURE);
  }

  stack->top = -1;
  stack->capacity = capacity;
  stack->items = (int *)malloc(stack->capacity * sizeof(int));
  if (!stack->items) {
    fprintf(stderr, "Error: Out of space!!! Exiting...\n");
    exit(EXIT_FAILURE);
  }

  return stack;
}

/* function to free a stack. */
void free_stack(stack_t *stack) {
  if (stack) {
    if (stack->items) {
      free(stack->items);
      stack->items = NULL;
    }

    free(stack);
    stack = NULL;
  }
}

/* Stack is full when top is equal to the last index */
int is_full(stack_t *stack) { return stack->top == stack->capacity - 1; }

/* Stack is empty when top is equal to -1 */
int is_empty(stack_t *stack) { return stack->top == -1; }

/* Function to add an item to stack.  It increases top by 1 */
void push(stack_t *stack, int item) {
  if (is_full(stack)) {
    puts("Warning: full stack push!!!");
    return;
  }

  stack->items[++(stack->top)] = item;
}

/* Function to remove an item from stack.  It decreases top by 1 */
int pop(stack_t *stack) {
  if (is_empty(stack)) {
    puts("Warning: empty stack pop!!!");
    return INT_MIN;
  }

  return stack->items[(stack->top)--];
}

/* Function to get the top item from stack. It does not decreases the top */
int peek(stack_t *stack) {
  if (is_empty(stack)) {
    puts("Warning: empty stack peek!!!");
    return INT_MIN;
  }

  return stack->items[stack->top];
}

/* Driver program to test above functions */
int main() {
  stack_t *stack = create_stack(100);

  push(stack, 10);
  push(stack, 20);
  push(stack, 30);

  printf("%d popped from stack\n", pop(stack));
  printf("%d popped from stack\n", pop(stack));
  printf("%d popped from stack\n", pop(stack));
  printf("%d popped from stack\n", pop(stack));

  return 0;
}