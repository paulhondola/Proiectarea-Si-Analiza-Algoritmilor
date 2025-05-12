#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_queue(queue *queue) {
  queue->front = 0;
  queue->rear = 0;
}

int is_full_queue(queue *queue) { return queue->rear >= MAX_QUEUE_SIZE; }

int is_empty_queue(queue *queue) { return queue->front == queue->rear; }

void enqueue(queue *queue, int value) {
  if (is_full_queue(queue)) {
    fprintf(stderr, "Queue overflow\n");
    return;
  }
  queue->data[queue->rear++] = value;
}

int dequeue(queue *queue) {
  if (is_empty_queue(queue)) {
    fprintf(stderr, "Queue underflow\n");
    return -1;
  }

  // printf("dequeue %d\n", queue->data[queue->front]);
  return queue->data[queue->front++];
}

int peek_queue(queue *queue) {
  if (is_empty_queue(queue)) {
    fprintf(stderr, "Queue is empty\n");
    return -1;
  }

  return queue->data[queue->front];
}

void print_queue(queue *queue) {
  for (int i = queue->front; i < queue->rear; i++) {
    printf("%d ", queue->data[i]);
  }
  printf("\n");
}
