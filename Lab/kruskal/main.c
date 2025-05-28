#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ----------------------
// Defines
// ----------------------

#define MAX_NODES 50

#define ENABLE_DEBUG 1

// ----------------------
// Structures
// ----------------------

typedef struct Graf {
  int numberOfNodes;
  int adjacencyMatrix[MAX_NODES][MAX_NODES];
} Graf_T;

// ---------------------------------
// data strucuture for a queue
// ---------------------------------

typedef struct Queue {
  int data[MAX_NODES];
  int front;
  int rear;
} Queue_t;

// ---------------------------------
// data structure for a stack
// ---------------------------------

typedef struct Stack {
  int data[MAX_NODES];
  int top;
} Stack_t;

// ===================================
// Queue functions
// ===================================

// (1) Initialize the queue

void initQueue(Queue_t *queue) {
  queue->front = -1;
  queue->rear = -1;
  memset(queue->data, 0, sizeof(queue->data));
}

// (2) Check if the queue is empty

int isQueueEmpty(Queue_t *queue) { return queue->front == -1; }

// (3) Check if the queue is full

int isQueueFull(Queue_t *queue) { return queue->rear == MAX_NODES - 1; }

// (4) Enqueue an element

void enqueue(Queue_t *queue, int valueAdded) {
  // check if there is space in the queue
  if (isQueueFull(queue)) {
    perror("Queue is full");
    return;
  }

  // check if the queue is empty
  if (isQueueEmpty(queue)) {
    // set the front to 0 in order to add the first element
    queue->front = 0;
  }

  // add the element to the queue
  queue->rear++;

  queue->data[queue->rear] = valueAdded;
}

// (5) Dequeue an element

int dequeue(Queue_t *queue) {
  // check if the queue is empty
  if (isQueueEmpty(queue)) {
    perror("Queue is empty");
    return -1;
  }

  // get the element from the front of the queue
  int valueRemoved = queue->data[queue->front];

  // check if the queue has only one element
  if (queue->front == queue->rear) {
    // reset the queue
    queue->front = -1;
    queue->rear = -1;
  } else {
    // move the front to the next element
    for (int i = 0; i < queue->rear; i++) {
      queue->data[i] = queue->data[i + 1];
    }
    queue->rear--;
  }

  return valueRemoved;
}

// (6) Get the front element
int getFront(Queue_t *queue) {
  // check if the queue is empty
  if (isQueueEmpty(queue)) {
    perror("Queue is empty");
    return -1;
  }
  // return the front element
  return queue->data[queue->front];
}

// (7) Get the rear element
int getRear(Queue_t *queue) {
  // check if the queue is empty
  if (isQueueEmpty(queue)) {
    perror("Queue is empty");
    return -1;
  }
  // return the rear element
  return queue->data[queue->rear];
}

// (8) Print the queue
void printQueue(Queue_t *queue) {
  // check if the queue is empty
  if (isQueueEmpty(queue)) {
    perror("Queue is empty");
    return;
  }
  // print the elements in the queue
  for (int i = queue->front; i <= queue->rear; i++) {
    printf("%d ", queue->data[i]);
  }
  printf("\n");
}

// ====================================
// stack functions
// ====================================

// (1) Initialize the stack

void initStack(Stack_t *stack) {
  stack->top = -1;
  memset(stack->data, 0, sizeof(stack->data));
}

// (2) Check if the stack is empty
int isStackEmpty(Stack_t *stack) { return stack->top == -1; }

// (3) Check if the stack is full
int isStackFull(Stack_t *stack) { return stack->top == MAX_NODES - 1; }

// (4) Push an element

void push(Stack_t *stack, int valueAdded) {
  // check if there is space in the stack
  if (isStackFull(stack)) {
    perror("Stack is full");
    return;
  }

  // add the element to the stack
  stack->top++;
  stack->data[stack->top] = valueAdded;
}

// (5) Pop an element

int pop(Stack_t *stack) {
  // check if the stack is empty
  if (isStackEmpty(stack)) {
    perror("Stack is empty");
    return -1;
  }

  // get the element from the top of the stack and decrease the top
  int poppedValue = stack->data[stack->top];
  stack->top--;

  return poppedValue;
}

// (6) Get the top element
int getTop(Stack_t *stack) {
  // check if the stack is empty
  if (isStackEmpty(stack)) {
    perror("Stack is empty");
    return -1;
  }

  // return the top element
  return stack->data[stack->top];
}

// (7) Print the stack

void printStack(Stack_t *stack) {
  // check if the stack is empty
  if (isStackEmpty(stack)) {
    perror("Stack is empty");
    return;
  }
  // print the elements in the stack
  // this is in the order that will pop the elements
  for (int i = stack->top; i >= 0; i--) {
    printf("%d ", stack->data[i]);
  }

  printf("\n");
}

// ----------------------
// Graf Functions
// ----------------------

void initGraf(Graf_T *graf) { memset(graf, 0, sizeof(Graf_T)); }

void readFromFile(Graf_T *graf, FILE *fin) {
  int from, to, weight;

  while (fscanf(fin, "\n%d %d %d", &from, &to, &weight) == 3) {
    // printf("DATA: %d %d %d\n", from, to, weight);
    graf->adjacencyMatrix[from][to] = weight;
  }
}

void printGraf(const Graf_T *graf) {
  int i, j;
  printf("Number of Nodes: %d\n", graf->numberOfNodes);
  printf("Adjacency Matrix:\n");
  for (i = 0; i < graf->numberOfNodes; i++) {
    for (j = 0; j < graf->numberOfNodes; j++) {
      printf("%d ", graf->adjacencyMatrix[i][j]);
    }
    printf("\n");
  }
}

// function to add an edge to the adjacency matrix
void addEdge(Graf_T *graf, int u, int v, int weight) {
  if (u < 0 || u >= graf->numberOfNodes || v < 0 || v >= graf->numberOfNodes) {
    fprintf(stderr, "Error: Node index out of bounds.\n");
    return;
  }
  graf->adjacencyMatrix[u][v] = weight;
  graf->adjacencyMatrix[v][u] = weight; // For undirected graph
}

// --------------------
// Different functions
// --------------------

// Function to find the minimum edge in the adjacency matrix

int findMinEdge(const Graf_T *graf, int visited[]) {
  int min = INT_MAX;
  int u = -1, v = -1;

  for (int i = 0; i < graf->numberOfNodes; i++) {
    if (visited[i]) {
      for (int j = 0; j < graf->numberOfNodes; j++) {
        if (!visited[j] && graf->adjacencyMatrix[i][j] > 0 &&
            graf->adjacencyMatrix[i][j] < min) {
          min = graf->adjacencyMatrix[i][j];
          u = i;
          v = j;
        }
      }
    }
  }

  return (u != -1 && v != -1) ? min : -1;
}

// ----------------------
// ALGORITHMS
// ----------------------

// PRIM's Algorithm -> U -> nodes visited with minimum cost ; N - U -> nodes not
// visited we start with a node, add it to U, then we look for the minimum edge
// that connects a node in U with a node not in U

void primAlgorithm(Graf_T *graf, int startNode) {
  // this visited array holds place for U
  int visited[MAX_NODES] = {0};

  // other variables
  int totalCost = 0;

  // initialize the visited array
  visited[startNode] = 1;

  printf("Prim's Algorithm starting from node %d:\n", startNode);

  // this for loop will run for (numberOfNodes - 1) times, because we need to
  // add (numberOfNodes - 1) edges to the MST
  for (int i = 1; i < graf->numberOfNodes; i++) {
    int minCostPerEdge = INT_MAX;
    int u = -1;
    int v = -1;

    // this for loop will find the minimum edge that connects a node in U with a
    // node not in U
    for (int j = 0; j < graf->numberOfNodes; j++) {
      // we check if the node is visited
      if (visited[j] == 1) {
        // if it s visited, we check the edges that connect it with nodes not in
        // U
        for (int k = 0; k < graf->numberOfNodes; k++) {
          // if the edge exists and the node is not visited
          if (graf->adjacencyMatrix[j][k] > 0 && visited[k] == 0) {
            // we have an eligible edge and we check if it is the minimum cost
            // edge
            if (graf->adjacencyMatrix[j][k] < minCostPerEdge) {
              minCostPerEdge = graf->adjacencyMatrix[j][k];
              u = j; // the node in U
              v = k; // the node not in U
            }
          }
        }
      }
    }

    // if we found an edge, we add it to the MST
    if (u != -1 && v != -1) {
      visited[v] = 1;              // mark the node as visited
      totalCost += minCostPerEdge; // add the cost of the edge to the total cost
      printf("Edge from %d to %d with cost %d\n", u, v, minCostPerEdge);
    } else {
      printf("No more edges to add.\n");
      break; // if no more edges are found, we break the loop
    }
  }

  printf("Total cost of the Minimum Spanning Tree: %d\n", totalCost);
}

// KRUSKAL's Algorithm
// we have a set of edges, we sort them by cost, then we add them to the MST if
// they do not create a cycle

void kruskalAlgorithm(Graf_T *graf) {
  // an array for every edge set
  int S[MAX_NODES] = {0};

  int totalCost = 0;

  // we initialize this array so that every node is its own set
  for (int i = 0; i < graf->numberOfNodes; i++) {
    S[i] = i;
  }

  for (int pas = 0; pas < graf->numberOfNodes - 1; pas++) {
    int minCost = INT_MAX;
    int u = -1;
    int v = -1;

    // find the minimum edge that connects two different sets
    for (int i = 0; i < graf->numberOfNodes; i++) {
      for (int j = 0; j < graf->numberOfNodes; j++) {
        if (graf->adjacencyMatrix[i][j] > 0 && S[i] != S[j] &&
            graf->adjacencyMatrix[i][j] < minCost) {
          minCost = graf->adjacencyMatrix[i][j];
          u = i; // the node in the first set
          v = j; // the node in the second set
        }
      }
    }

    for (int i = 0; i < graf->numberOfNodes; i++) {
      if (S[i] == S[v]) {
        S[i] = S[u]; // merge the two sets
      }
    }

    if (u != -1 && v != -1) {
      printf("Edge from %d to %d with cost %d\n", u, v, minCost);
      totalCost += minCost; // add the cost of the edge to the total cost
    } else {
      printf("No more edges to add.\n");
      break; // if no more edges are found, we break the loop
    }
  }

  printf("Total cost of the Minimum Spanning Tree: %d\n", totalCost);
}

//	---------------------
// MAIN
// ----------------------

int main(int argc, char **argv) {
  if (argc != 2) {
    perror("Usage: ./main <filename>");
    return 1;
  }

  FILE *fin = fopen(argv[1], "r");

  if (fin == NULL) {
    perror("Error opening file");
    return 1;
  }

  Graf_T graf;
  initGraf(&graf);

  int numberOfNodes;

  if (fscanf(fin, "%d", &numberOfNodes) != 1) {
    perror("Error reading number of nodes from file");
    fclose(fin);
    return 1;
  }

  graf.numberOfNodes = numberOfNodes;

  if (graf.numberOfNodes > MAX_NODES) {
    fprintf(stderr, "Error: Number of nodes exceeds maximum limit of %d\n",
            MAX_NODES);
    fclose(fin);
    return 1;
  }

  readFromFile(&graf, fin);

  if (ENABLE_DEBUG) {
    printf("-------------------\n");
    printGraf(&graf);
    printf("-------------------\n");
  }

  // Run Prim's algorithm starting from node 0
  printf("---------------------\n");
  primAlgorithm(&graf, 0);
  printf("---------------------\n");

  // Run Kruskal's algorithm
  printf("---------------------\n");
  kruskalAlgorithm(&graf);
  printf("---------------------\n");

  fclose(fin);
  return 0;
}
