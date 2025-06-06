#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_stack(stack *stack) { stack->top = 0; }

int is_full_stack(stack *stack) { return stack->top >= MAX_STACK_SIZE; }

int is_empty_stack(stack *stack) { return stack->top == 0; }

void push(stack *stack, int value) {
  if (is_full_stack(stack)) {
    fprintf(stderr, "Stack overflow\n");
    return;
  }

  stack->data[stack->top++] = value;
}

int pop(stack *stack) {
  if (is_empty_stack(stack)) {
    fprintf(stderr, "Stack underflow\n");
    return -1;
  }

  return stack->data[--stack->top];
}

int peek_stack(stack *stack) {
  if (is_empty_stack(stack)) {
    fprintf(stderr, "Stack is empty\n");
    return -1;
  }
  return stack->data[stack->top - 1];
}

void print_stack(stack *stack) {
  if (is_empty_stack(stack)) {
    fprintf(stderr, "Stack is empty\n");
    return;
  }

  for (int i = 0; i < stack->top; i++) {
    printf("%d ", stack->data[i]);
  }
  printf("\n");
}
