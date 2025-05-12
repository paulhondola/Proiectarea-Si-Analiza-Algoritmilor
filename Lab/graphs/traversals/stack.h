#ifndef __STACK_H__
#define __STACK_H__

#define MAX_STACK_SIZE 128

typedef struct {
	int data[MAX_STACK_SIZE];
	int top;
} stack_t;

// init, pop, push, peek, is_empty, is_full

void init_stack(stack_t* stack);
void push(stack_t* stack, int value);
int pop(stack_t* stack);
int peek_stack(stack_t* stack);
int is_empty_stack(stack_t* stack);
int is_full_stack(stack_t* stack);
void print_stack(stack_t* stack);

#endif