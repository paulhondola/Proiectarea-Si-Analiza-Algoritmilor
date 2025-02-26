#include <stdio.h>

int main(void) {
  int arr[] = {1, 2, 3, 4};

  for (int i = 0; i < 4; i++) {
    printf("%d ", i[arr]);
  }

  printf("\n");

  for (int i = 0; i < 4; i++) {
    printf("%d ", *arr + i);
  }
}
