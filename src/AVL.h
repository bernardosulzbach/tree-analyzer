#ifndef AVL_H
#define AVL_H

#include "constants.h"
#include "report.h"
#include <stdlib.h>

typedef struct AVL {
  Key key;
  Element data;
  int height;
  struct AVL *left;
  struct AVL *right;
  Report report;
} AVL;

void AVL_initialize(AVL **root);

void AVL_free(AVL **root);

int AVL_is_empty(AVL *tree);

size_t AVL_size(AVL *tree);

/**
 * Returns whether or not the tree contains an element with the specified key.
 */
int AVL_contains(Report *report, AVL *tree, Key key);

/**
 * Returns the element associated with the specified key in the Binary Search
 * Tree or NULL_ELEMENT if the key is not present in the tree.
 */
Element AVL_get(Report *report, AVL *tree, Key key);

void AVL_insert(Report *report, AVL **root, Key key, Element element);

void AVL_remove(Report *report, AVL **root, Key key);

void print_AVL_tree(AVL *tree);

#endif
