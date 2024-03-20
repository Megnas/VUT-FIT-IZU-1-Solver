#include "nodeSet.h"
#include <stdbool.h>
#include <stdlib.h>

NodeSet *init_node_set() {
  NodeSet *set = malloc(sizeof(NodeSet));
  if (set == NULL) {
    return NULL;
  }
  set->first = NULL;

  return set;
}
void dispose_node_set(NodeSet **nodeSet) {
  NodeSetNode *node = (*nodeSet)->first;
  while (node != NULL) {
    NodeSetNode *next = node->next;
    free(node);
    node = next;
  }
  free(*nodeSet);
  *nodeSet = NULL;
}
int node_set_push_back(NodeSet *nodeSet, int arrayId) {
  NodeSetNode *newNode = malloc(sizeof(NodeSetNode));
  if (newNode == NULL) {
    return 1;
  }

  newNode->arrayId = arrayId;
  newNode->next = NULL;

  NodeSetNode *currentNode = nodeSet->first;
  if (currentNode == NULL) {
    nodeSet->first = newNode;
    newNode->before = NULL;
    return 0;
  }

  while (currentNode->next != NULL) {
    currentNode = currentNode->next;
  }

  currentNode->next = newNode;
  newNode->before = currentNode;

  return 0;
}

bool node_set_contains(NodeSet *nodeSet, int arrayId) {
  for (NodeSetNode *node = nodeSet->first; node != NULL; node = node->next) {
    if (arrayId == node->arrayId) {
      return true;
    }
  }
  return false;
}

NodeSetNode *node_set_pop_lowest(NodeSet *nodeSet, NodeArray *array) {
  NodeSetNode *lowestNode = nodeSet->first;
  if (lowestNode == NULL) {
    return NULL;
  }

  for (NodeSetNode *currentNode = lowestNode->next; currentNode != NULL;
       currentNode = currentNode->next) {
    int currentCost = (array->arr)[currentNode->arrayId].pathCost;
    int lowestCost = (array->arr)[lowestNode->arrayId].pathCost;
    if (currentCost < lowestCost) {
      lowestNode = currentNode;
    } else if (currentNode == lowestNode) {
      if (lowestNode->arrayId > currentNode->arrayId) {
        lowestNode = currentNode;
      }
    }
  }

  NodeSetNode *next = lowestNode->next;
  NodeSetNode *prev = lowestNode->before;

  if (next != NULL) {
    next->before = prev;
  }

  if (prev != NULL) {
    prev->next = next;
  } else {
    nodeSet->first = next;
  }

  lowestNode->next = NULL;
  lowestNode->before = NULL;

  return lowestNode;
}
void node_set_insert(NodeSet *nodeSet, NodeSetNode *node) {
  NodeSetNode *currentNode = nodeSet->first;
  if (currentNode == NULL) {
    nodeSet->first = node;
    return;
  }

  while (currentNode->next != NULL) {
    currentNode = currentNode->next;
  }

  currentNode->next = node;
  node->before = currentNode;
}
