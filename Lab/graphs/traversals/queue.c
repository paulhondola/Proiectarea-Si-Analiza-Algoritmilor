#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void init_queue(queue_t* queue) {
	queue->front = 0;
	queue->rear = 0;
}

int is_full_queue(queue_t* queue) {
	return queue->rear >= MAX_QUEUE_SIZE;
}

int is_empty_queue(queue_t* queue) {
	return queue->front == queue->rear;
}

void enqueue(queue_t* queue, int value) {
	if (is_full_queue(queue)) {
		fprintf(stderr, "Queue overflow\n");
		return;
	}
	queue->data[queue->rear++] = value;
}

int dequeue(queue_t* queue) {
	if (is_empty_queue(queue)) {
		fprintf(stderr, "Queue underflow\n");
		return -1;
	}

	printf("dequeue %d\n", queue->data[queue->front]);
	return queue->data[queue->front++];
}

int peek_queue(queue_t* queue) {
	if (is_empty_queue(queue)) {
		fprintf(stderr, "Queue is empty\n");
		return -1;
	}

	return queue->data[queue->front];
}

void print_queue(queue_t* queue) {
	for (int i = queue->front; i < queue->rear; i++) {
		printf("%d ", queue->data[i]);
	}
	printf("\n");
}