#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "constants.h"
#include <stdlib.h>

typedef struct AVLTree {
  Key key;
  Element data;
  int height;
  struct AVLTree *left;
  struct AVLTree *right;
} AVLTree;

void AVL_tree_initialize(AVLTree **root);
void AVL_tree_free(AVLTree **root);

int AVL_tree_is_empty(AVLTree *tree);

size_t AVL_tree_size(AVLTree *tree);

/**
 * Returns whether or not the tree contains an element with the specified key.
 */
int AVL_tree_contains(AVLTree *tree, Key key);

/**
 * Returns the element associated with the specified key in the Binary Search
 * Tree or NULL_ELEMENT if the key is not present in the tree.
 */
Element AVL_tree_get(AVLTree *tree, Key key);

void AVL_tree_insert(AVLTree **root, Key key, Element element);

void AVL_tree_remove(AVLTree **root, Key key);

void print_AVL_tree(AVLTree *tree);

#endif
