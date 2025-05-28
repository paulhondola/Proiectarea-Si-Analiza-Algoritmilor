#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_GRAPH_SIZE 26

typedef struct {
  int matrix[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE];
  char nodes[MAX_GRAPH_SIZE];
  int node_count;
} graph;

int get_index(graph *g, char c) {

  for (int i = 0; i < g->node_count; i++) {
    if (g->nodes[i] == c) {
      return i;
    }
  }

  fprintf(stderr, "Node %c not found in graph\n", c);
  exit(EXIT_FAILURE);
}

void init_graph(graph *g) { memset(g, 0, sizeof(graph)); }

void read_graph(graph *g, FILE *f) {

  // read the number of nodes
  if (fscanf(f, "%d\n", &g->node_count) != 1) {
    fprintf(stderr, "Error reading number of nodes\n");
    exit(EXIT_FAILURE);
  }

  // read the nodes names
  for (int i = 0; i < g->node_count; i++) {
    if (fscanf(f, "%c ", &g->nodes[i]) != 1) {
      fprintf(stderr, "Error reading node name\n");
      exit(EXIT_FAILURE);
    }
  }

  // read the edges
  char from, to;
  int weight;

  while (1) {

    if (fscanf(f, "\n%c %c %d", &from, &to, &weight) != 3) {
      if (feof(f))
        break; // end of file reached
      fprintf(stderr, "Error reading edge\n");
      exit(EXIT_FAILURE);
    }

    int from_index = get_index(g, from);
    int to_index = get_index(g, to);

    if (from_index < 0 || from_index >= g->node_count || to_index < 0 ||
        to_index >= g->node_count) {
      fprintf(stderr, "Node index out of bounds\n");
      exit(EXIT_FAILURE);
    }

    g->matrix[from_index][to_index] = weight;
  }
}

void print_graph(const graph *g) {
  for (int i = 0; i < g->node_count; i++) {
    printf("%c ", g->nodes[i]);
  }

  printf("\n");

  for (int i = 0; i < g->node_count; i++) {
    printf("==");
  }

  printf("\n");

  for (int i = 0; i < g->node_count; i++) {
    for (int j = 0; j < g->node_count; j++)
      printf("%d ", g->matrix[i][j]);

    printf("\n");
  }
}

void dijkstra(graph *g, char start_node) {
  int start = get_index(g, start_node);
  int dist[MAX_GRAPH_SIZE];
  bool visited[MAX_GRAPH_SIZE] = {false};
  int prev[MAX_GRAPH_SIZE];

  for (int i = 0; i < g->node_count; i++) {
    dist[i] = INT_MAX;
    prev[i] = -1;
  }

  dist[start] = 0;

  for (int count = 0; count < g->node_count - 1; count++) {
    int next = -1;
    int min_dist = INT_MAX;

    // Find the unvisited node with the smallest distance
    for (int i = 0; i < g->node_count; i++) {
      if (!visited[i] && dist[i] < min_dist) {
        min_dist = dist[i];
        next = i;
      }
    }

    if (next == -1)
      break; // no reachable nodes left

    visited[next] = true;

    // go through all neighbors of the next node
    // if the node is unvisited and the distance can be improved
    // update the distance and previous node
    for (int i = 0; i < g->node_count; i++) {
      if (!visited[i] && g->matrix[next][i] != 0 &&
          g->matrix[next][i] != INT_MAX &&
          dist[i] > dist[next] + g->matrix[next][i]) {
        dist[i] = dist[next] + g->matrix[next][i];
        prev[i] = next;
      }
    }
  }

  // Print paths
  for (int i = 0; i < g->node_count; i++) {
    if (i == start)
      continue;

    printf("Shortest path to %c (cost %d): ", g->nodes[i], dist[i]);

    if (dist[i] == INT_MAX) {
      printf("unreachable\n");
      continue;
    }

    // Reconstruct path
    int path[MAX_GRAPH_SIZE];
    int path_len = 0;
    for (int v = i; v != -1; v = prev[v]) {
      path[path_len++] = v;
    }

    for (int j = path_len - 1; j >= 0; j--) {
      printf("%c", g->nodes[path[j]]);

      if (j > 0)
        printf(" -> ");
    }
    printf("\n");
  }
}

int main(int argc, char *argv[]) {

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <starting_node>\n", argv[0]);
    return 1;
  }

  char start_node = argv[1][0];

  FILE *f = fopen("graf.txt", "r");
  if (f == NULL) {
    perror("Failed to open file");
    return 2;
  }

  graph g;
  init_graph(&g);
  read_graph(&g, f);
  fclose(f);
  print_graph(&g);

  dijkstra(&g, start_node);

  return 0;
}
