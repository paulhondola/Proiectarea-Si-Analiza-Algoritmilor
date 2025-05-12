#ifndef __QUEUE_H__
#define __QUEUE_H__

#define MAX_QUEUE_SIZE 128

typedef struct {
	int data[MAX_QUEUE_SIZE];
	int front;
	int rear;
} queue_t;

// init, enqueue, dequeue, peek, is_empty, is_full

void init_queue(queue_t* queue);
void enqueue(queue_t* queue, int value);
int dequeue(queue_t* queue);
int peek_queue(queue_t* queue);
int is_empty_queue(queue_t* queue);
int is_full_queue(queue_t* queue);
void print_queue(queue_t* queue);

#endif