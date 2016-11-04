#ifndef BST_H
#define BST_H

#include <stdlib.h>

#include "constants.h"

typedef struct BinarySearchTree {
  Key key;
  Element data;
  struct BinarySearchTree *left;
  struct BinarySearchTree *right;
} BinarySearchTree;

void binary_search_tree_initialize(BinarySearchTree **root);
void binary_search_tree_free(BinarySearchTree **root);

int binary_search_tree_is_empty(BinarySearchTree *tree);

size_t binary_search_tree_size(BinarySearchTree *tree);

/**
 * Returns whether or not the tree contains an element with the specified key.
 */
int binary_search_tree_contains(BinarySearchTree *tree, Key key);

/**
 * Returns the element associated with the specified key in the Binary Search
 * Tree or NULL_ELEMENT if the key is not present in the tree.
 */
Element binary_search_tree_get(BinarySearchTree *tree, Key key);

void binary_search_tree_insert(BinarySearchTree **root, Key key,
                               Element element);

void binary_search_tree_remove(BinarySearchTree **root, Key key);

void print_binary_search_tree(BinarySearchTree *tree);

#endif
