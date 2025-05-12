#ifndef __STACK_H__
#define __STACK_H__

#define MAX_STACK_SIZE 128

typedef struct {
  int data[MAX_STACK_SIZE];
  int top;
} stack;

// init, pop, push, peek, is_empty, is_full

void init_stack(stack *);
void push(stack *, int);
int pop(stack *);
int peek_stack(stack *);
int is_empty_stack(stack *);
int is_full_stack(stack *);
void print_stack(stack *);

#endif
