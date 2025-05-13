#include <math.h>
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
  for (int i = 1; i <= size; i++) {
    for (int j = 1; j <= size; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}

void bfs(int matrix[][MAX_MATRIX_SIZE], int size, int start) {

  int visited[MAX_MATRIX_SIZE] = {0};
  queue q;
  init_queue(&q);

  // enqueue the starting node
  enqueue(&q, start);
  visited[start] = 1;

  while (!is_empty_queue(&q)) {
    int current = dequeue(&q);
    printf("%d ", current);

    // visit all the neighbors of the current node
    for (int i = 1; i <= size; i++) {
      if (matrix[current][i] && !visited[i]) {
        enqueue(&q, i);
        visited[i] = 1;
      }
    }
  }
}

void dfs(int matrix[][MAX_MATRIX_SIZE], int size, int start) {
  stack s;
  init_stack(&s);

  int visited[MAX_MATRIX_SIZE] = {0};

  // push the starting node
  push(&s, start);
  visited[start] = 1;

  while (!is_empty_stack(&s)) {
    int current = pop(&s);
    printf("%d ", current);

    // visit all the neighbors of the current node
    for (int i = size; i >= 1; i--) {
      if (matrix[current][i] && !visited[i]) {
        push(&s, i);
        visited[i] = 1;
      }
    }
  }
}

int shortest_path(int matrix[][MAX_MATRIX_SIZE], int size, int start, int end) {

  int visited[MAX_MATRIX_SIZE] = {0};
  int path[MAX_MATRIX_SIZE] = {0};

  stack s;
  init_stack(&s);

  // push the starting node
  push(&s, start);
  visited[start] = 1;

  while (!is_empty_stack(&s)) {
    int current = pop(&s);
    // printf("%d ", current);

    // visit all the neighbors of the current node
    for (int i = size; i >= 1; i--) {
      if (matrix[current][i] && !visited[i]) {
        push(&s, i);
        visited[i] = 1;
        path[i] = path[current] + 1;
      }
    }
  }

  // reconstruct the path from start to end
  if (!visited[end]) {
    printf("No path found\n");
    return -1;
  }

  return path[end];
}

void dfs_no_lib(int matrix[][MAX_MATRIX_SIZE], int size, int start) {
  int visited[MAX_MATRIX_SIZE] = {0};
  int stack[MAX_MATRIX_SIZE] = {0};
  int top = 0;

  stack[top++] = start;
  visited[start] = 1;

  while (top) {
    // pop the last node
    int current = stack[--top];
    printf("%d ", current);

    // add all the nodes next to current
    for (int i = size; i >= 1; i--) {
      if (matrix[current][i] && !visited[i]) {
        stack[top++] = i;
        visited[i] = 1;
      }
    }
  }

  printf("\n");
}

void bfs_no_lib(int matrix[][MAX_MATRIX_SIZE], int size, int start) {
  int queue[MAX_MATRIX_SIZE] = {0};
  int visited[MAX_MATRIX_SIZE] = {0};
  int front = 0, rear = 0;

  queue[rear++] = start;
  visited[start] = 1;

  while (front != rear) {
    int current = queue[front++];
    printf("%d ", current);

    for (int i = 1; i <= size; i++) {
      if (matrix[current][i] && !visited[i]) {
        queue[rear++] = i;
        visited[i] = 1;
      }
    }
  }

  printf("\n");
}

int conex_structures(int matrix[][MAX_MATRIX_SIZE], int size) {
  int count = 0;

  int visited[MAX_MATRIX_SIZE] = {0};

  for (int i = 1; i <= size; i++) {
    if (!visited[i]) {
      count++;
      // BFS or DFS to mark all nodes in this component
      queue q;
      init_queue(&q);
      enqueue(&q, i);
      visited[i] = 1;

      while (!is_empty_queue(&q)) {
        int current = dequeue(&q);

        for (int j = 1; j <= size; j++) {
          if (matrix[current][j] && !visited[j]) {
            enqueue(&q, j);
            visited[j] = 1;
          }
        }
      }
    }
  }

  return count;
}

int main(void) {
  FILE *f = fopen("date.txt", "r");

  if (!f) {
    perror("date.txt");
    return EXIT_FAILURE;
  }

  int size = 0;
  int matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
  memset(matrix, 0, sizeof(matrix));

  read_matrix_data(matrix, &size, f);
  fclose(f);

  print_matrix(matrix, size);

  printf("\n");

  /*

  // BFS starting from node 1
  printf("BFS starting from node 1:\n");
  bfs(matrix, size, 1);

  printf("\n");
  // DFS starting from node 1
  printf("DFS starting from node 1:\n");
  dfs(matrix, size, 1);

  // Shortest path from node 1 to node 5
  printf("\nShortest path from node 1 to node 5:\n");
  printf("%d\n", shortest_path(matrix, size, 1, 5));

  // Number of connected components
  printf("Number of connected components: ");
  int components = conex_structures(matrix, size);
  printf("%d\n", components);
  */

  dfs(matrix, size, 1);
  dfs_no_lib(matrix, size, 1);
  bfs(matrix, size, 1);
  bfs_no_lib(matrix, size, 1);

  return 0;
}
