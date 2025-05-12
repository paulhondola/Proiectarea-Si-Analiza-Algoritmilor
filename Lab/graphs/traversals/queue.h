#ifndef __QUEUE_H__
#define __QUEUE_H__

#define MAX_QUEUE_SIZE 128

typedef struct {
  int data[MAX_QUEUE_SIZE];
  int front;
  int rear;
} queue;

// init, enqueue, dequeue, peek, is_empty, is_full

void init_queue(queue *);
void enqueue(queue *, int);
int dequeue(queue *);
int peek_queue(queue *);
int is_empty_queue(queue *);
int is_full_queue(queue *);
void print_queue(queue *);

#endif
