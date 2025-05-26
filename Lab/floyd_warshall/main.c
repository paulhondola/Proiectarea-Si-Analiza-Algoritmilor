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
  for (int i = 0; i <= g->node_count; i++)
    for (int j = 0; j <= g->node_count; j++)
      g->matrix[i][j] = INT_MAX;

  // set self edges to 0
  for (int i = 0; i <= g->node_count; i++)
    g->matrix[i][i] = 0;

  // read the nodes values and weights
  int from, to, weight;

  while (fscanf(f, "%d %d %d\n", &from, &to, &weight) == 3)
    g->matrix[from][to] = weight;
}

void print_graph(const graph *g) {
  printf("Graph with %d nodes:\n", g->node_count);
  for (int i = 1; i <= g->node_count; i++) {
    for (int j = 1; j <= g->node_count; j++) {
      if (g->matrix[i][j] == INT_MAX)
        printf("INF ");
      else
        printf("%d ", g->matrix[i][j]);
    }
    printf("\n");
  }
}

void print_roads_aux(const graph *distances, const graph *roads, int i, int j,
                     int *cost) {
  int k = roads->matrix[i][j];
  if (k) {
    print_roads_aux(distances, roads, i, k, cost);
    *cost = distances->matrix[i][k] + distances->matrix[k][j];
    printf("%d -> ", k);
    print_roads_aux(distances, roads, k, j, cost);
  }
}

void print_roads(const graph *distances, const graph *roads, int i, int j) {
  int cost = 0;
  printf("Road from %d to %d:\n", i, j);
  printf("%d -> ", i);
  print_roads_aux(distances, roads, i, j, &cost);
  printf("%d\n", j);
  printf("Total Cost: %d\n", cost);
}

void floyd(graph *g, graph *distances, graph *roads) {
  // init matrix
  memcpy(distances, g, sizeof(graph));
  memset(roads, 0, sizeof(graph));
  roads->node_count = g->node_count;

  for (int k = 1; k <= g->node_count; k++) {
    for (int i = 1; i <= g->node_count; i++) {
      for (int j = 1; j <= g->node_count; j++) {
        if (distances->matrix[i][k] != INT_MAX &&
            distances->matrix[k][j] != INT_MAX) {
          int new_road = distances->matrix[i][k] + distances->matrix[k][j];
          if (distances->matrix[i][j] > new_road) {
            distances->matrix[i][j] = new_road;
            roads->matrix[i][j] = k;
          }
        }
      }
    }
  }
}

void warshall(graph *w, graph *distances) {

  w->node_count = distances->node_count;
  for (int i = 0; i <= distances->node_count; i++)
    for (int j = 0; j <= distances->node_count; j++)
      w->matrix[i][j] =
          distances->matrix[i][j] != 0 && distances->matrix[i][j] != INT_MAX;

  for (int k = 1; k <= w->node_count; k++) {
    for (int i = 1; i <= w->node_count; i++) {
      for (int j = 1; j <= w->node_count; j++) {
        if (w->matrix[i][j] == 0)
          w->matrix[i][j] = w->matrix[i][k] && w->matrix[k][j];
      }
    }
  }
}

int main(void) {

  FILE *f = fopen("graf.txt", "r");
  if (!f) {
    fprintf(stderr, "Error opening file\n");
    return EXIT_FAILURE;
  }

  graph g, distances, roads, w;
  read_graph(&g, f);

  fclose(f);

  floyd(&g, &distances, &roads);

  print_graph(&g);
  print_graph(&distances);
  print_graph(&roads);

  print_roads(&distances, &roads, 1, 2);

  warshall(&w, &distances);
  print_graph(&w);

  return 0;
}
