#ifndef NODE_SET_HEADER
#define NODE_SET_HEADER

#include "2dField.h"
#include <stdbool.h>

struct node_set_node {
  struct node_set_node *next;
  struct node_set_node *before;
  int arrayId;
} typedef NodeSetNode;

struct node_set {
  NodeSetNode *first;
} typedef NodeSet;

NodeSet *init_node_set();
void dispose_node_set(NodeSet **nodeSet);
int node_set_push_back(NodeSet *nodeSet, int arrayId);
bool node_set_contains(NodeSet *nodeSet, int arrayId);
NodeSetNode *node_set_pop_lowest(NodeSet *nodeSet, NodeArray *array);
void node_set_insert(NodeSet *nodeSet, NodeSetNode *node);

#define IS_SET_EMPTY(nodeset) ((nodeset)->first == NULL)

#endif
