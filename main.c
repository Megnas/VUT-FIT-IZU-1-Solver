#include "2dField.h"
#include "nodeSet.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void ParseHeader(int *xSize, int *ySize, Pos *start, Pos *end) {
  scanf("%d %d\n", xSize, ySize);
  scanf("%d %d\n", &(start->x), &(start->y));
  scanf("%d %d\n", &(end->x), &(end->y));
}

NodeArray *ParseInput(int xSize, int ySize) {
  NodeArray *arr = alloc_array(xSize, ySize);

  if (arr == NULL) {
    exit(1);
  }

  for (int y = 0; y < ySize; y++) {
    for (int x = 0; x < xSize; x++) {
      int val;
      scanf("%d", &val);

      ARR_GET_VALUE(arr, x, y).cost = val;
      ARR_GET_VALUE(arr, x, y).parrent = -1;
      ARR_GET_VALUE(arr, x, y).pathCost = -1;
    }
  }

  return arr;
}

bool isPartOfPath(NodeArray *arr, Pos finish, Pos current) {
  int currentNodeIndex = ARR_GET_INDEX(arr, current.x, current.y);
  int searchedNodeIndex = ARR_GET_VALUE(arr, finish.x, finish.y).parrent;
  while (searchedNodeIndex != -1) {
    if (searchedNodeIndex == currentNodeIndex)
      return true;

    searchedNodeIndex = ARR_GET_VALUE_INDEX(arr, searchedNodeIndex).parrent;
  }
  return false;
}

void print_set(NodeSet *set, NodeArray *arr) {
  NodeSetNode *node = set->first;
  while (node != NULL) {

    Pos target = GET_POSITION(node->arrayId, arr);
    int value = ARR_GET_VALUE_INDEX(arr, node->arrayId).pathCost;
    int parrent = ARR_GET_VALUE_INDEX(arr, node->arrayId).parrent;
    if (parrent >= 0) {
      Pos parrentPos = GET_POSITION(parrent, arr);
      printf("([%d, %d], %d, [%d, %d])", target.x, target.y, value,
             parrentPos.x, parrentPos.y);
    } else {
      printf("([%d, %d], %d, null)", target.x, target.y, value);
    }

    if (node->next != NULL) {
      printf(", ");
    }

    node = node->next;
  }
  printf("\n");
}

void find_path(NodeArray *arr, Pos start, Pos finish, bool showDebug) {
  NodeSet *open = init_node_set();
  NodeSet *closed = init_node_set();

  if (open == NULL || closed == NULL) {
    exit(1);
  }

  node_set_push_back(open, ARR_GET_INDEX(arr, start.x, start.y));
  ARR_GET_VALUE(arr, start.x, start.y).pathCost = 0;
  int cnt = 1;
  while (1) {

    NodeSetNode *lowest = node_set_pop_lowest(open, arr);
    if (lowest == NULL) {
      fprintf(stderr, "Path does not exists!\n");
      break;
    }
    Pos lowestPos = GET_POSITION(lowest->arrayId, arr);

    if (lowestPos.x == finish.x && lowestPos.y == finish.y) {
      printf("Path found\n");
      node_set_insert(closed, lowest);
      break;
    }

    // printf("[%d %d]\n", lowestPos.x, lowestPos.y);
    int lowestPathCost = ARR_GET_VALUE(arr, lowestPos.x, lowestPos.y).pathCost;
    // Loop trough all neighbours
    for (int y = lowestPos.y - 1; y <= lowestPos.y + 1; y++) {
      for (int x = lowestPos.x - 1; x <= lowestPos.x + 1; x++) {
        // Check if is in bounds
        if (x >= 0 && y >= 0 && x < arr->xSize && y < arr->ySize) {
          // Check if not looping trough center
          if (!(x == lowestPos.x && y == lowestPos.y)) {
            int arrIndex = ARR_GET_INDEX(arr, x, y);
            if (!node_set_contains(closed, arrIndex)) {
              int currentCost = ARR_GET_VALUE_INDEX(arr, arrIndex).cost;
              // Check if is not wall
              if (currentCost > 0) {
                int newPathCost = currentCost + lowestPathCost;
                int currentPathCost =
                    ARR_GET_VALUE_INDEX(arr, arrIndex).pathCost;
                // Never visited
                if (currentPathCost == -1) {
                  ARR_GET_VALUE_INDEX(arr, arrIndex).pathCost = newPathCost;
                  ARR_GET_VALUE_INDEX(arr, arrIndex).parrent = lowest->arrayId;
                  node_set_push_back(open, arrIndex);
                } else { // Was visited
                  if (newPathCost < currentPathCost) {
                    ARR_GET_VALUE_INDEX(arr, arrIndex).pathCost = newPathCost;
                    ARR_GET_VALUE_INDEX(arr, arrIndex).pathCost =
                        lowest->arrayId;
                  }
                }
              }
            }
          }
        }
      }
    } // END OF FOR

    node_set_insert(closed, lowest);

    printf("%d iteration of algorithm: \n", cnt);
    for (int y = 0; y < ARR_HEIGHT(arr); y++) {
      for (int x = 0; x < ARR_WIDTH(arr); x++) {
        int val = ARR_GET_VALUE(arr, x, y).cost;
        int arrIndex = ARR_GET_INDEX(arr, x, y);
        if (val == 0) // WALL
          printf("\033[0;40m Z \033[0m");
        else if (x == start.x && y == start.y) // START
          printf("\033[0;42m %d \033[0m", val);
        else if (x == finish.x && y == finish.y) // FINISH
          printf("\033[0;41m %d \033[0m", val);
        else if (node_set_contains(open, arrIndex)) // OPEN
          printf("\033[0;44m %d \033[0m", val);
        else if (node_set_contains(closed, arrIndex)) // CLOSED
          printf("\033[0;45m %d \033[0m", val);
        else // JUST VALUE
          printf(" %d ", val);
      }
      printf("\n");
    }
    printf("\n");
    if (showDebug) {

      printf("Open set: \n");
      print_set(open, arr);
      printf("Closed set: \n");
      print_set(closed, arr);
      printf("\n");
    }
    // LOOP BREAK CONDITION
    cnt++;
    // if (cnt == 10)
    //   break;
  }

  printf("Found path on %d iteration: \n", cnt);
  for (int y = 0; y < ARR_HEIGHT(arr); y++) {
    for (int x = 0; x < ARR_WIDTH(arr); x++) {
      int val = ARR_GET_VALUE(arr, x, y).cost;
      int arrIndex = ARR_GET_INDEX(arr, x, y);
      if (val == 0) // WALL
        printf("\033[0;40m Z \033[0m");
      else if (x == start.x && y == start.y) // START
        printf("\033[0;42m %d \033[0m", val);
      else if (x == finish.x && y == finish.y) // FINISH
        printf("\033[0;41m %d \033[0m", val);
      else if (isPartOfPath(arr, finish, (Pos){x, y}))
        printf("\033[0;43m %d \033[0m", val);
      else if (node_set_contains(open, arrIndex)) // OPEN
        printf("\033[0;44m %d \033[0m", val);
      else if (node_set_contains(closed, arrIndex)) // CLOSED
        printf("\033[0;45m %d \033[0m", val);
      else // JUST VALUE
        printf(" %d ", val);
    }
    printf("\n");
  }
  printf("\n");

  if (showDebug) {
    printf("Open set: \n");
    print_set(open, arr);
    printf("Closed set: \n");
    print_set(closed, arr);
    printf("\n");
  }
  dispose_node_set(&open);
  dispose_node_set(&closed);
}

int main(int argc, char *argv[]) {

  bool showDebug = false;

  int opt;
  while ((opt = getopt(argc, argv, "hd")) != -1) {
    switch (opt) {
    case 'd':
      showDebug = true;
      break;
    case 'h':
      printf("Usage: %s [-d] [-h]\n", argv[0]);
      exit(0);
    default:
      fprintf(stderr, "Usage: %s [-h] [-d]\n", argv[0]);
      exit(1);
    }
  }

  Pos start;
  Pos finish;
  int xSize, ySize;
  ParseHeader(&xSize, &ySize, &start, &finish);
  NodeArray *arr = ParseInput(xSize, ySize);

  printf("Inputed array: \n");
  print_array(arr);

  find_path(arr, start, finish, showDebug);

  dispose_array(&arr);
  return 0;
}
