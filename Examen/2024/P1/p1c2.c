/*
Write, in C, the necessary data structures and algorithms which do the
following: • Create a dynamically allocated linked list of nodes with 32 bit
unsigned integers as data payload based on whitespace separated values from a
file: The name of the file, which contains full relevant path, will be the only
command line argument for your compiled program. The size of this: file is not
considered known. • Sort this list so when traversed from the beginning to end
it will generate an ordered sequence of those 32 bit unsigned integers, without
touching the same node more than once: • Traverse this list only one time and
print the values of each node to the standard output. Values will be separated
by one space: The last value: will also have one space after it. This will
output an ordered sequences for those values..
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
  uint32_t data;
  struct NODE *next;
} *node;

node create_node(uint32_t data) {
  node n = malloc(sizeof(struct NODE));
  if (n == NULL) {
    perror("malloc");
    exit(1);
  }
  n->data = data;
  n->next = NULL;
  return n;
}

node insert_ordered_node(node head, node n) {
  if (head == NULL) {
    return n;
  }

  if (n->data < head->data) {
    n->next = head;
    return n;
  }

  node current = head;

  while (current->next != NULL && n->data > current->next->data)
    current = current->next;

  n->next = current->next;
  current->next = n;

  return head;
}

node create_ordered_list(node head, FILE *fp) {

  while (!feof(fp)) {
    uint32_t data = 0;
    if (fscanf(fp, "%u", &data) != 1)
      break;

    node n = create_node(data);
    head = insert_ordered_node(head, n);
  }
  return head;
}

void print_list(node head) {
  if (head) {
    printf("%u -> ", head->data);
    print_list(head->next);
  }
}

int main(int argc, char **argv) {

  if (argc != 2) {
    printf("Usage: %s <file>\n", argv[0]);
    return 1;
  }

  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
    perror("fopen");
    return 1;
  }

  node head = create_ordered_list(NULL, fp);
  print_list(head);
  printf("\n");

  return 0;
}
