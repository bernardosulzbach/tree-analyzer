#include "AVL.h"
#include <stdio.h>
#include <stdlib.h>

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
AVLTree *create_AVL_node(Key key, Element element) {
  AVLTree *tree;
  tree = malloc(sizeof(AVLTree));
  if (tree != NULL) {
    tree->key = key;
    tree->data = element;
    tree->height = 1;
    tree->left = NULL;
    tree->right = NULL;
  }
  return tree;
}

static int max(int a, int b) {
  if (b > a) {
    return b;
  }
  return a;
}

/**
 * Removes the element with the smallest key from the tree and returns a
 * pointer to it.
 */
static AVLTree *detach_smallest(AVLTree **root) {
  AVLTree *iter = *root;
  AVLTree *prev = iter;
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
static AVLTree *detach_greatest(AVLTree **root) {
  AVLTree *iter = *root;
  AVLTree *prev = iter;
  while (iter != NULL && iter->right != NULL) {
    prev = iter;
    iter = iter->right;
  }
  if (iter != NULL && iter != prev) {
    prev->right = iter->left;
  }
  return iter;
}

void print_AVL_tree_indented(AVLTree *tree, int level) {
  int i;
  if (tree->right != NULL) {
    print_AVL_tree_indented(tree->right, level + DEFAULT_INDENT);
  }
  for (i = 0; i < level; i++) {
    printf(" ");
  }
  print_key(tree->key);
  printf(" -> ");
  print_element(tree->data);
  printf("\n");
  if (tree->left != NULL) {
    print_AVL_tree_indented(tree->left, level + DEFAULT_INDENT);
  }
}

/*
 * From this point onwards is defined the public interface of the Binary Search
 * Tree.
 */

void AVL_tree_initialize(AVLTree **root) { *root = NULL; }

void AVL_tree_free(AVLTree **root) {
  AVLTree *tree = *root;
  if (tree != NULL) {
    AVL_tree_free(&tree->left);
    AVL_tree_free(&tree->right);
    free(tree);
  }
  *root = NULL;
}

int AVL_tree_is_empty(AVLTree *tree) { return tree == NULL; }

size_t AVL_tree_size(AVLTree *tree) {
  size_t count = 0;
  if (tree != NULL) {
    count = 1;
    count += AVL_tree_size(tree->left);
    count += AVL_tree_size(tree->right);
  }
  return count;
}

/**
 * Returns whether or not the tree contains an element with the specified key.
 */
int AVL_tree_contains(AVLTree *tree, Key key) {
  return AVL_tree_get(tree, key) != NULL_ELEMENT;
}

/**
 * Returns the element associated with the specified key in the Binary Search
 * Tree or NULL_ELEMENT if the key is not present in the tree.
 */
Element AVL_tree_get(AVLTree *tree, Key key) {
  Element element = NULL_ELEMENT;
  if (tree != NULL) {
    if (tree->key == key) {
      element = tree->data;
    } else if (key_less_than(key, tree->key)) {
      element = AVL_tree_get(tree->left, key);
    } else {
      element = AVL_tree_get(tree->right, key);
    }
  }
  return element;
}

static int get_balance(AVLTree *tree) {
  int balance = 0;
  if (tree != NULL) {
    if (tree->left != NULL) {
      balance += tree->left->height;
    }
    if (tree->right != NULL) {
      balance -= tree->right->height;
    }
  }
  return balance;
}

static int get_height(AVLTree *tree) {
  if (tree != NULL) {
    return tree->height;
  }
  return 0;
}

static void update_height(AVLTree *root) {
  root->height = max(get_height(root->left), get_height(root->right)) + 1;
}

void rotate_right(AVLTree **root) {
  AVLTree *tree = *root;
  AVLTree *swap;
  swap = tree->left;
  tree->left = swap->right;
  swap->right = tree;
  tree = swap;
  update_height(tree->right);
  update_height(tree);
  *root = tree;
}

void rotate_left(AVLTree **root) {
  AVLTree *tree = *root;
  AVLTree *swap;
  swap = tree->right;
  tree->right = swap->left;
  swap->left = tree;
  tree = swap;
  update_height(tree->left);
  update_height(tree);
  *root = tree;
}

void rebalance(AVLTree **root) {
  AVLTree *tree = *root;
  if (tree != NULL) {
    if (get_balance(tree) < -1) {
      if (get_balance(tree->left) > 0) {
        rotate_right(&tree->left);
      }
      rotate_left(root);
    } else if (get_balance(tree) > 1) {
      if (get_balance(tree->left) < 0) {
        rotate_left(&tree->left);
      }
      rotate_right(root);
    }
  }
}

/**
 * Inserts the (key, element) pair in the tree if it does not exist yet or
 * changes the element currently pointed by
 */
void AVL_tree_insert(AVLTree **root, Key key, Element element) {
  AVLTree *tree = *root;
  if (tree == NULL) {
    *root = create_AVL_node(key, element);
  } else {
    if (tree->key == key) {
      tree->data = element;
    } else if (key_less_than(key, tree->key)) {
      AVL_tree_insert(&tree->left, key, element);
      tree->height = max(get_height(tree->left), get_height(tree->right)) + 1;
      rebalance(root);
    } else {
      AVL_tree_insert(&tree->right, key, element);
      tree->height = max(get_height(tree->left), get_height(tree->right)) + 1;
      rebalance(root);
    }
  }
}

void AVL_tree_remove(AVLTree **root, Key key) {
  AVLTree *tree = *root;
  AVLTree *left = NULL;
  AVLTree *right = NULL;
  AVLTree *replacement = NULL;
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
        *root = replacement;
        tree->height = max(get_height(tree->left), get_height(tree->right)) + 1;
        rebalance(root);
      } else {
        *root = NULL;
      }
    } else if (key_less_than(key, tree->key)) {
      /* Propagate removal to the left child. */
      AVL_tree_remove(&tree->left, key);
      tree->height = max(get_height(tree->left), get_height(tree->right)) + 1;
      rebalance(root);
    } else {
      /* Propagate removal to the right child. */
      AVL_tree_remove(&tree->right, key);
      tree->height = max(get_height(tree->left), get_height(tree->right)) + 1;
      rebalance(root);
    }
  }
}

size_t AVL_tree_depth(AVLTree *tree) {
  size_t left_depth;
  size_t right_depth;
  size_t maximum_child_depth;
  if (tree == NULL) {
    return 0;
  }
  left_depth = AVL_tree_depth(tree->left);
  right_depth = AVL_tree_depth(tree->right);
  if (left_depth >= right_depth) {
    maximum_child_depth = left_depth;
  } else {
    maximum_child_depth = right_depth;
  }
  return 1 + maximum_child_depth;
}

void print_AVL_tree(AVLTree *tree) {
  if (tree == NULL) {
    printf("Empty tree.\n");
  } else {
    print_AVL_tree_indented(tree, 0);
  }
}
