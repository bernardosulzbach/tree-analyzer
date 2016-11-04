#include <stdio.h>

#include "AVL.h"
#include "BST.h"
#include "report.h"

static Report last_report;

static AVLTree *avl_root = NULL;
static BinarySearchTree *bst_root = NULL;

void insert_values(char *filename) { printf("Inserting from %s\n", filename); }

void query_values(char *filename) { printf("Querying from %s\n", filename); }

void remove_values(char *filename) { printf("Removing from %s\n", filename); }

void statistics(void) {
  printf("Statistics for the last operation:\n");
  printf("Time: %ld ms\n", last_report.time);
  printf("Nodes: %ld\n", last_report.nodes);
  printf("Height: %ld\n", last_report.height);
  printf("Factor: %ld\n", last_report.factor);
  printf("Comparisons: %ld\n", last_report.comparisons);
  printf("Roations: %ld\n", last_report.rotations);
}

void execute_instructions(char *filename) {
  /* See roteiro.txt to understand the format. */
  /* Parse the file pointed to by filename, calling the functions above. */
}

int main(int argc, char **argv) {
  /* Should have a valid report at all times. */
  last_report = report_create();
  binary_search_tree_initialize(&bst_root);
  AVL_tree_initialize(&avl_root);
  if (argc < 2) {
    printf("Pass a filename to the program.\n");
  } else if (argc == 2) {
    execute_instructions(argv[1]);
  } else {
    printf("Pass just a filename to the program.\n");
  }
  binary_search_tree_free(&bst_root);
  AVL_tree_free(&avl_root);
  return 0;
}
