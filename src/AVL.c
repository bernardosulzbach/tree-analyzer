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
AVL *create_AVL_node(Key key, Element element) {
  AVL *tree;
  tree = malloc(sizeof(AVL));
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
static AVL *detach_smallest(AVL **root) {
  AVL *iter = *root;
  AVL *prev = iter;
  if (iter == NULL) {
    return NULL;
  }
  while (iter->left != NULL) {
    prev = iter;
    iter = iter->left;
  }
  if (iter != prev) {
    prev->left = iter->right;
  }
  return iter;
}

/**
 * Removes the element with the greatest key from the tree and returns a
 * pointer to it.
 */
static AVL *detach_greatest(AVL **root) {
  AVL *iter = *root;
  AVL *prev = iter;
  if (iter == NULL) {
    return NULL;
  }
  while (iter->right != NULL) {
    prev = iter;
    iter = iter->right;
  }
  if (iter != prev) {
    prev->right = iter->left;
  }
  return iter;
}

void print_AVL_indented(AVL *tree, int level) {
  int i;
  if (tree->right != NULL) {
    print_AVL_indented(tree->right, level + DEFAULT_INDENT);
  }
  for (i = 0; i < level; i++) {
    printf(" ");
  }
  print_key(tree->key);
  printf(" -> ");
  print_element(tree->data);
  printf("\n");
  if (tree->left != NULL) {
    print_AVL_indented(tree->left, level + DEFAULT_INDENT);
  }
}

/*
 * From this point onwards is defined the public interface of the Binary Search
 * Tree.
 */

void AVL_initialize(AVL **root) { *root = NULL; }

void AVL_free(AVL **root) {
  AVL *tree = *root;
  if (tree != NULL) {
    AVL_free(&tree->left);
    AVL_free(&tree->right);
    free(tree);
  }
  *root = NULL;
}

int AVL_is_empty(AVL *tree) { return tree == NULL; }

size_t AVL_size(AVL *tree) {
  size_t count = 0;
  if (tree != NULL) {
    count = 1;
    count += AVL_size(tree->left);
    count += AVL_size(tree->right);
  }
  return count;
}

/**
 * Returns whether or not the tree contains an element with the specified key.
 */
int AVL_contains(Report *report, AVL *tree, Key key) {
  return AVL_get(report, tree, key) != NULL_ELEMENT;
}

/**
 * Returns the element associated with the specified key in the Binary Search
 * Tree or NULL_ELEMENT if the key is not present in the tree.
 */
Element AVL_get(Report *report, AVL *tree, Key key) {
  Element element = NULL_ELEMENT;
  if (tree != NULL) {
    /* Will make a comparison. */
    report->comparisons++;
    if (tree->key == key) {
      element = tree->data;
    } else if (key_less_than(key, tree->key)) {
      element = AVL_get(report, tree->left, key);
    } else {
      element = AVL_get(report, tree->right, key);
    }
  }
  return element;
}

static int get_balance(AVL *tree) {
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

static int AVL_height(AVL *tree) {
  if (tree != NULL) {
    return tree->height;
  }
  return 0;
}

static long AVL_balance_factor(AVL *tree) {
  long balance_here;
  long factor_here;
  long factor_left;
  long factor_right;
  if (tree == NULL) {
    return 0;
  }
  balance_here = get_balance(tree);
  factor_here = labs(balance_here);
  factor_left = AVL_balance_factor(tree->left);
  factor_right = AVL_balance_factor(tree->right);
  if (factor_left > factor_here) {
    factor_here = factor_left;
  }
  if (factor_left > factor_here) {
    factor_here = factor_right;
  }
  return factor_here;
}

static void update_height(AVL *root) {
  root->height = max(AVL_height(root->left), AVL_height(root->right)) + 1;
}

static void rotate_right(AVL **root) {
  AVL *tree = *root;
  AVL *swap;
  swap = tree->left;
  tree->left = swap->right;
  swap->right = tree;
  tree = swap;
  update_height(tree->right);
  update_height(tree);
  *root = tree;
}

static void rotate_left(AVL **root) {
  AVL *tree = *root;
  AVL *swap;
  swap = tree->right;
  tree->right = swap->left;
  swap->left = tree;
  tree = swap;
  update_height(tree->left);
  update_height(tree);
  *root = tree;
}

void rebalance(Report *report, AVL **root) {
  AVL *tree = *root;
  if (tree != NULL) {
    /* Tree is right heavy. */
    if (get_balance(tree) < -1) {
      /* Right subtree is left-heavy. */
      if (get_balance(tree->right) > 0) {
        rotate_right(&tree->right);
        report->rotations++;
      }
      rotate_left(root);
      report->rotations++;
    }
    /* Tree is left heavy. */
    else if (get_balance(tree) > 1) {
      /* Left subtree is right-heavy. */
      if (get_balance(tree->left) < 0) {
        rotate_left(&tree->left);
        report->rotations++;
      }
      rotate_right(root);
      report->rotations++;
    }
  }
}

/**
 * Inserts the (key, element) pair in the tree if it does not exist yet or
 * changes the element currently pointed by
 */
void AVL_insert(Report *report, AVL **root, Key key, Element element) {
  AVL *tree = *root;
  if (tree == NULL) {
    *root = create_AVL_node(key, element);
  } else {
    report->comparisons++;
    if (tree->key == key) {
      tree->data = element;
    } else if (key_less_than(key, tree->key)) {
      AVL_insert(report, &tree->left, key, element);
      update_height(tree);
      rebalance(report, root);
    } else {
      AVL_insert(report, &tree->right, key, element);
      update_height(tree);
      rebalance(report, root);
    }
  }
}

void AVL_remove(Report *report, AVL **root, Key key) {
  AVL *tree = *root;
  AVL *left = NULL;
  AVL *right = NULL;
  AVL *replacement = NULL;
  if (tree != NULL) {
    report->comparisons++;
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
          replacement->left = left->left;
        }
        if (right != replacement) {
          replacement->right = right;
        } else {
          replacement->right = right->right;
        }
        *root = replacement;
        tree->height = max(AVL_height(tree->left), AVL_height(tree->right)) + 1;
        rebalance(report, root);
      } else {
        *root = NULL;
      }
    } else if (key_less_than(key, tree->key)) {
      /* Propagate removal to the left child. */
      AVL_remove(report, &tree->left, key);
      tree->height = max(AVL_height(tree->left), AVL_height(tree->right)) + 1;
      rebalance(report, root);
    } else {
      /* Propagate removal to the right child. */
      AVL_remove(report, &tree->right, key);
      tree->height = max(AVL_height(tree->left), AVL_height(tree->right)) + 1;
      rebalance(report, root);
    }
  }
}

void AVL_update_report(Report *report, AVL *tree) {
  report->nodes = AVL_size(tree);
  report->height = AVL_height(tree);
  report->factor = AVL_balance_factor(tree);
}

void print_AVL_tree(AVL *tree) {
  if (tree == NULL) {
    printf("Empty tree.\n");
  } else {
    print_AVL_indented(tree, 0);
  }
}
