#ifndef BST_H
#define BST_H

#include "constants.h"
#include "report.h"
#include <stdlib.h>

typedef struct BST {
  Key key;
  Element data;
  struct BST *left;
  struct BST *right;
  Report report;
} BST;

void BST_initialize(BST **root);
void BST_free(BST **root);

int BST_is_empty(BST *tree);

size_t BST_size(BST *tree);

/**
 * Returns whether or not the tree contains an element with the specified key.
 */
int BST_contains(Report *report, BST *tree, Key key);

/**
 * Returns the element associated with the specified key in the Binary Search
 * Tree or NULL_ELEMENT if the key is not present in the tree.
 */
Element BST_get(Report *report, BST *tree, Key key);

void BST_insert(Report *report, BST **root, Key key, Element element);

void BST_remove(Report *report, BST **root, Key key);

void BST_print(BST *tree);

#endif
