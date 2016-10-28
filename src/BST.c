#include <stdio.h>
#include <stdlib.h>

#include "BST.h"

#define DEFAULT_INDENT 2

/*
 * From this point onwards is defined the private interface of the Binary Search
 * Tree.
 */

/**
 * Allocates a new Binary Search Tree with the specified key and element in the
 * root node and null children.
 *
 * If memory allocation fails, NULL is returned.
 */
BinarySearchTree *create_node(Key key, Element element) {
  BinarySearchTree *tree;
  tree = malloc(sizeof(BinarySearchTree));
  if (tree != NULL) {
    tree->key = key;
    tree->data = element;
    tree->left = NULL;
    tree->right = NULL;
  }
  return tree;
}

/**
 * Removes the element with the smallest key from the tree and returns a
 * pointer to it.
 */
BinarySearchTree *detach_smallest(BinarySearchTree **root) {
  BinarySearchTree *iter = *root;
  BinarySearchTree *prev = iter;
  while (iter != NULL && iter->left != NULL) {
    prev = iter;
    iter = iter->left;
  }
  if (iter != NULL && iter != prev) {
    prev->left = iter->right;
  }
  return iter;
}

/**
 * Removes the element with the greatest key from the tree and returns a
 * pointer to it.
 */
BinarySearchTree *detach_greatest(BinarySearchTree **root) {
  BinarySearchTree *iter = *root;
  BinarySearchTree *prev = iter;
  while (iter != NULL && iter->right != NULL) {
    prev = iter;
    iter = iter->right;
  }
  if (iter != NULL && iter != prev) {
    prev->right = iter->left;
  }
  return iter;
}

void print_binary_search_tree_indented(BinarySearchTree *tree, int level) {
  int i;
  if (tree->left != NULL) {
    print_binary_search_tree_indented(tree->left, level + DEFAULT_INDENT);
  }
  for (i = 0; i < level; i++) {
    printf(" ");
  }
  print_key(tree->key);
  printf(" -> ");
  print_element(tree->data);
  printf("\n");
  if (tree->right != NULL) {
    print_binary_search_tree_indented(tree->right, level + DEFAULT_INDENT);
  }
}

/*
 * From this point onwards is defined the public interface of the Binary Search
 * Tree.
 */

void binary_search_tree_initialize(BinarySearchTree **root) { *root = NULL; }

void binary_search_tree_free(BinarySearchTree **root) {
  BinarySearchTree *tree = *root;
  if (tree != NULL) {
    binary_search_tree_free(&tree->left);
    binary_search_tree_free(&tree->right);
    free(tree);
  }
  *root = NULL;
}

int binary_search_tree_is_empty(BinarySearchTree *tree) { return tree == NULL; }

size_t binary_search_tree_size(BinarySearchTree *tree) {
  size_t count = 0;
  if (tree != NULL) {
    count = 1;
    count += binary_search_tree_size(tree->left);
    count += binary_search_tree_size(tree->right);
  }
  return count;
}

/**
 * Returns whether or not the tree contains an element with the specified key.
 */
int binary_search_tree_contains(BinarySearchTree *tree, Key key) {
  return binary_search_tree_get(tree, key) != NULL_ELEMENT;
}

/**
 * Returns the element associated with the specified key in the Binary Search
 * Tree or NULL_ELEMENT if the key is not present in the tree.
 */
Element binary_search_tree_get(BinarySearchTree *tree, Key key) {
  Element element = NULL_ELEMENT;
  if (tree != NULL) {
    if (tree->key == key) {
      element = tree->data;
    } else if (key_less_than(key, tree->key)) {
      element = binary_search_tree_get(tree->left, key);
    } else {
      element = binary_search_tree_get(tree->right, key);
    }
  }
  return element;
}

/**
 * Inserts the (key, element) pair in the tree if it does not exist yet or
 * changes the element currently pointed by
 */
void binary_search_tree_insert(BinarySearchTree **root, Key key,
                               Element element) {
  BinarySearchTree *tree = *root;
  if (tree == NULL) {
    *root = create_node(key, element);
  } else {
    if (tree->key == key) {
      tree->data = element;
    } else if (key_less_than(key, tree->key)) {
      binary_search_tree_insert(&tree->left, key, element);
    } else {
      binary_search_tree_insert(&tree->right, key, element);
    }
  }
}

void binary_search_tree_remove(BinarySearchTree **root, Key key) {
  BinarySearchTree *tree = *root;
  BinarySearchTree *left = NULL;
  BinarySearchTree *right = NULL;
  BinarySearchTree *replacement = NULL;
  if (tree != NULL) {
    if (tree->key == key) {
      if (tree->left != NULL) {
        replacement = detach_greatest(&tree->left);
      } else if (tree->right != NULL) {
        replacement = detach_smallest(&tree->right);
      }
      left = tree->left;
      right = tree->right;
      free(tree);
      if (replacement != NULL) {
        /* Update the replacement to fit its new position. */
        /* Ensure that we do not insert a cycle in the tree. */
        if (left != replacement) {
          replacement->left = left;
        } else {
          replacement->left = NULL;
        }
        if (right != replacement) {
          replacement->right = right;
        } else {
          replacement->right = NULL;
        }
        tree = replacement;
      } else {
        tree = NULL;
      }
    } else if (key_less_than(key, tree->key)) {
      /* Propagate removal to the left child. */
      binary_search_tree_remove(&tree->left, key);
    } else {
      /* Propagate removal to the right child. */
      binary_search_tree_remove(&tree->right, key);
    }
  }
  /* Write back any changes that have been made. */
  *root = tree;
}

BinarySearchTree *lowest_common_ancestor(BinarySearchTree *tree, Key a, Key b) {
  if (tree == NULL) {
    return NULL;
  }
  if (tree->key != a && tree->key != b) {
    if (key_less_than(a, tree->key) && key_less_than(b, tree->key)) {
      return lowest_common_ancestor(tree->left, a, b);
    } else if (key_less_than(tree->key, a) && key_less_than(tree->key, b)) {
      return lowest_common_ancestor(tree->right, a, b);
    }
  }
  return tree;
}

size_t binary_search_tree_depth(BinarySearchTree *tree) {
  size_t left_depth;
  size_t right_depth;
  size_t maximum_child_depth;
  if (tree == NULL) {
    return 0;
  }
  left_depth = binary_search_tree_depth(tree->left);
  right_depth = binary_search_tree_depth(tree->right);
  if (left_depth >= right_depth) {
    maximum_child_depth = left_depth;
  } else {
    maximum_child_depth = right_depth;
  }
  return 1 + maximum_child_depth;
}

void print_binary_search_tree(BinarySearchTree *tree) {
  if (tree == NULL) {
    printf("Empty tree.\n");
  } else {
    print_binary_search_tree_indented(tree, 0);
  }
}
