#define _CRT_SECURE_NO_WARNINGS
#include "queue.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MATRIX_SIZE 50

void read_matrix_data(int matrix[][MAX_MATRIX_SIZE], int *size, FILE *f) {
  // read the first line, the size of the matrix
  if (fscanf(f, "%d\n", size) != 1 || *size < 1 || *size > MAX_MATRIX_SIZE) {
    fprintf(stderr, "Invalid matrix size\n");
    exit(EXIT_FAILURE);
  }

  // fprintf(stderr, "Matrix size %d\n", *size);

  while (1) {

    // read until eof
    int i = 0, j = 0;

    // the input is 2 numbers per line, marks the edges of the matrix
    int read = fscanf(f, "%d %d\n", &i, &j);

    if (read == EOF)
      break;
    else if (read != 2) {
      fprintf(stderr, "Invalid input format\n");
      exit(EXIT_FAILURE);
    }

    matrix[i][j] = matrix[j][i] = 1;
  }
}

void print_matrix(int matrix[][MAX_MATRIX_SIZE], int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}

void stack_test() {
  stack stack;

  init_stack(&stack);

  for (int i = 0; i < 10; i++) {
    push(&stack, i);
  }

  print_stack(&stack);

  for (int i = 0; i < 5; i++) {
    pop(&stack);
  }

  print_stack(&stack);

  printf("\n");
}

void queue_test() {
  queue queue;

  init_queue(&queue);

  for (int i = 0; i < 10; i++) {
    enqueue(&queue, i);
  }

  print_queue(&queue);

  for (int i = 0; i < 5; i++) {
    dequeue(&queue);
  }

  print_queue(&queue);
}

int main(void) {
  FILE *f = fopen("date.txt", "r");

  if (!f) {
    perror("date.txt");
    return EXIT_FAILURE;
  }

  int size = 0;
  int matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
  memset(matrix, 0, MAX_MATRIX_SIZE * MAX_MATRIX_SIZE);

  read_matrix_data(matrix, &size, f);
  fclose(f);

  print_matrix(matrix, size);

  printf("\n");

  stack_test();
  queue_test();

  return 0;
}
