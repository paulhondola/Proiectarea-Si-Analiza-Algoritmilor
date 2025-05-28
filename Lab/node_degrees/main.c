#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GRAPH_SIZE 20

typedef struct {
  int matrix[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE];
  int node_count;
} graph;

void read_graph(graph *g, FILE *f) {

  // read the number of nodes
  if (fscanf(f, "%d\n", &g->node_count) != 1) {
    fprintf(stderr, "Error reading number of nodes\n");
    exit(EXIT_FAILURE);
  }

  // init graph with INF
  for (int i = 0; i < g->node_count; i++)
    for (int j = 0; j < g->node_count; j++)
      g->matrix[i][j] = INT_MAX;

  // set self edges to 0
  for (int i = 0; i < g->node_count; i++)
    g->matrix[i][i] = 0;

  // read the nodes values and weights
  int from, to, weight;

  while (fscanf(f, "%d %d %d\n", &from, &to, &weight) == 3)
    g->matrix[from][to] = weight;
}

void print_graph(const graph *g) {
  printf("Graph with %d nodes:\n", g->node_count);
  for (int i = 0; i < g->node_count; i++) {
    for (int j = 0; j < g->node_count; j++) {
      if (g->matrix[i][j] == INT_MAX)
        printf("INF ");
      else
        printf("%d ", g->matrix[i][j]);
    }
    printf("\n");
  }
}

int is_edge(graph *g, int x, int y) {
  return g->matrix[x][y] != 0 && g->matrix[x][y] != INT_MAX;
}

int get_input_degree(graph *g, int node) {
  int deg = 0;
  for (int i = 0; i < g->node_count; i++)
    if (is_edge(g, i, node))
      deg++;
  return deg;
}

int get_output_degree(graph *g, int node) {
  int deg = 0;
  for (int i = 0; i < g->node_count; i++)
    if (is_edge(g, node, i))
      deg++;
  return deg;
}

void print_degrees(graph *g) {
  for (int i = 0; i < g->node_count; i++) {
    printf("NODE: %d\n", i);
    printf("Output degree: %d\n", get_output_degree(g, i));
    printf("Input degree: %d\n\n", get_input_degree(g, i));
  }
}

int main(int argc, char **argv) {

  if (argc != 2) {
    fprintf(stderr, "%s <filename>\n", argv[0]);
    return 1;
  }

  FILE *f = fopen(argv[1], "r");

  if (f == NULL) {
    perror(argv[1]);
    return 2;
  }

  graph g;
  read_graph(&g, f);
  print_graph(&g);
  print_degrees(&g);
  return 0;
}
