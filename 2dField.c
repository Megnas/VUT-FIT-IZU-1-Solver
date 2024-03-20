#include "2dField.h"
#include <stdio.h>
#include <stdlib.h>

NodeArray *alloc_array(int xSize, int ySize) {
  if (xSize <= 0 || ySize <= 0) {
    fprintf(stderr, "Can not allocte array of negative of zero size!\n");
    return NULL;
  }

  NodeArray *arr = malloc(sizeof(NodeArray));
  if (arr == NULL) {
    fprintf(stderr, "Failed to allocate memory for NodeArray structure!\n");
    return NULL;
  }

  arr->xSize = xSize;
  arr->ySize = ySize;

  arr->arr = malloc(sizeof(Node) * xSize * ySize);
  if (arr->arr == NULL) {
    fprintf(stderr, "Failed to allocte memory for NodeArray!\n");
    free(arr);
    return NULL;
  }

  return arr;
}

void dispose_array(NodeArray **array) {
  NodeArray *ptr = *array;
  if (ptr == NULL) {
    fprintf(stderr, "Trying to dispose non existing array!\n");
    return;
  }

  free(ptr->arr);
  free(ptr);

  *array = NULL;
}

void print_array(NodeArray *arr) {
  for (int y = 0; y < ARR_HEIGHT(arr); y++) {
    for (int x = 0; x < ARR_WIDTH(arr); x++) {
      int val = ARR_GET_VALUE(arr, x, y).cost;
      if (val == 0)
        printf("\033[0;40m Z \033[0m");
      else
        printf(" %d ", val);
    }
    printf("\n");
  }
}
