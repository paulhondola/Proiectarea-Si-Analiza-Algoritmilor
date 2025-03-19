#define _CRT_SECURE_NO_WARNINGS
#include "Bib.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

TTree bulkInsert(TTree a, FILE *f) {

  int x = 0, y = 0;

  while (fscanf(f, "%d %d", &y, &x) == 2) { // Ensures two values are read
    printf("Inserting %d %d\n", x, y);
    a = InsertNode(
        a, x, y); // Ensure InsertNode correctly returns the new tree structure
  }

  return a;
}

int main(int argc, char **argv) {

  if (argc != 2) {
    printf("Usage: %s <input_file>\n", argv[0]);
    return 1;
  }

  FILE *f = fopen(argv[1], "r");
  if (f == NULL) {
    printf("Could not open file %s\n", argv[1]);
    return 2;
  }

  TTree a = {0};
  a = InitTree(a);
  a = bulkInsert(a, f);

  TTree binaryTree = {0};
  printArray(a);

  printf("\npreOrder:\n");
  preOrder(a);
  printf("\ninOrder:\n");
  inOrder(a);
  printf("\npostOrder:\n");
  postOrder(a);

  fclose(f);

  return 0;
}
