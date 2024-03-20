#ifndef FIELD2D_HEADER
#define FIELD2D_HEADER

struct node {
  int cost;
  int parrent;
  int pathCost;
} typedef Node;

struct node_array {
  Node *arr;
  int xSize;
  int ySize;
} typedef NodeArray;

struct position {
  int x;
  int y;
} typedef Pos;

NodeArray *alloc_array(int xSize, int ySize);
void dispose_array(NodeArray **array);
void print_array(NodeArray *arr);

#define ARR_GET_VALUE(arr, x, y) ((arr)->arr[(x) + (y) * ((arr)->xSize)])
#define ARR_GET_INDEX(arr, x, y) ((x) + (y) * ((arr)->xSize))
#define ARR_GET_VALUE_INDEX(arr, index) ((arr)->arr[(index)])
#define ARR_WIDTH(arr) ((arr)->xSize)
#define ARR_HEIGHT(arr) ((arr)->ySize)

#define GET_POSITION(index, arr)                                               \
  { (index) % (arr)->xSize, (index) / (arr)->xSize }

#endif
