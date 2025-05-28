#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -----------------
// Defines
// -----------------

#define MAX_NODES 50

#define ENABLE_DEBUG 1

// -----------------
// Data Structures
// -----------------

// ----------------
// Graf
// -------------------

typedef struct Graf {
  int numberOfNodes;
  int adjacencyMatrix[MAX_NODES][MAX_NODES];
} Graf_T;

// -----------------
// Functions
// -----------------

// ----------------------
// Graf Functions
// ----------------------

void initGraf(Graf_T *graf) { memset(graf, 0, sizeof(Graf_T)); }

void readFromFile(Graf_T *graf, FILE *fin) {
  int i, j;

  for (i = 0; i < graf->numberOfNodes; i++) {
    for (j = 0; j < graf->numberOfNodes; j++) {
      if (fscanf(fin, "%d", &graf->adjacencyMatrix[i][j]) != 1) {
        perror("Error reading adjacency matrix from file");
        exit(EXIT_FAILURE);
      }
    }
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

// ALGORITHMS

void dijkstra(Graf_T *graf, int startNode) {
  // we ll use this array to mark the visited nodes
  int visited[MAX_NODES] = {0};

  // this array will be used in order to store the minimum cost to reach each
  // node
  int costArray[MAX_NODES] = {0};

  // this array we ll use to store the previous node in the path
  int previousNode[MAX_NODES] = {0};

  for (int i = 0; i < graf->numberOfNodes; i++) {
    costArray[i] = INT_MAX; // Initialize all costs to infinity
    previousNode[i] = -1;   // Initialize previous nodes to -1
  }

  // Cost to reach the start node is 0
  costArray[startNode] = 0;
  visited[startNode] = 1; // Mark the start node as visited

  int currentNode = startNode;

  // this for loop will iterate through all the nodes in the graph
  for (int pas = 0; pas < graf->numberOfNodes - 1; pas++) {
    int minCost = INT_MAX;

    // go through all the nodes to find the node with the minimum cost
    for (int i = 0; i < graf->numberOfNodes; i++) {
      if (!visited[i] && graf->adjacencyMatrix[currentNode][i] > 0) {
        if (costArray[i] >
            (costArray[currentNode] + graf->adjacencyMatrix[currentNode][i])) {
          costArray[i] =
              costArray[currentNode] + graf->adjacencyMatrix[currentNode][i];
          previousNode[i] = currentNode;
        }
      }
    }

    // Find the next node with the minimum cost
    for (int i = 0; i < graf->numberOfNodes; i++) {
      if (!visited[i] && costArray[i] < minCost) {
        minCost = costArray[i];
        currentNode = i;
      }
    }

    // Mark the current node as visited
    visited[currentNode] = 1;
  }

  // Print the results
  printf("Dijkstra's Algorithm Results:\n");

  printf("Node\tCost\tPrevious Node\n");

  for (int i = 0; i < graf->numberOfNodes; i++) {
    if (costArray[i] == INT_MAX) {
      printf("%d\tINF\t-\n", i);
    } else {
      printf("%d\t%d\t%d\n", i, costArray[i], previousNode[i]);
    }
  }

  printf("\nShortest paths from node %d:\n", startNode);

  for (int i = 0; i < graf->numberOfNodes; i++) {
    if (i == startNode)
      continue; // Skip the start node itself

    printf("Path to node %d: ", i);

    // reconstruct the path from the start node to node i
    int path[MAX_NODES];
    int pathIndex = 0;

    // Backtrack to find the path
    for (int j = i; j != -1; j = previousNode[j]) {
      path[pathIndex++] = j;
    }

    // Print the path in reverse order
    for (int j = pathIndex - 1; j >= 0; j--) {
      printf("%d ", path[j]);

      if (j > 0) {
        printf(" -> ");
      }
    }
    printf("\n");
  }

  printf("\n");
}

// ----------------------
// MAIN
// ----------------------

int main(int argc, char **argv) {
  if (argc != 2) {
    perror("Usage: ./main <filename>");
    return 1;
  }

  FILE *fin = fopen(argv[1], "r");

  if (!fin) {
    perror("Error opening file");
    return 1;
  }

  Graf_T graf;
  initGraf(&graf);

  if (fscanf(fin, "%d", &graf.numberOfNodes) != 1) {
    perror("Error reading number of nodes from file");
    fclose(fin);
    return 1;
  }

  if (graf.numberOfNodes <= 0 || graf.numberOfNodes > MAX_NODES) {
    perror("Invalid number of nodes");
    fclose(fin);
    return 1;
  }

  readFromFile(&graf, fin);

  if (ENABLE_DEBUG) {
    printf("-------------------------------\n");
    printGraf(&graf);
    printf("-------------------------------\n");
  }

  printf("--------------------------------\n");
  printf("Running Dijkstra's algorithm from node 0:\n");
  dijkstra(&graf, 0);
  printf("--------------------------------\n");

  fclose(fin);

  return 0;
}
