#include "AVL.h"
#include "BST.h"
#include "report.h"
#include <stdio.h>
#include <stdlib.h>

static Report bst_report;
static BST *bst_root = NULL;

static Report avl_report;
static AVL *avl_root = NULL;

void insert_values(char *filename) {
  FILE *file;
  int value;
  printf("Inserting from %s\n", filename);
  file = fopen(filename, "r");
  if (file) {
    bst_report = report_create();
    report_clock_start(&bst_report);
    while (fscanf(file, "%d", &value) != EOF) {
      BST_insert(&bst_report, &bst_root, value, value);
    }
    report_clock_stop(&bst_report);
    fclose(file); /* Close the stream before updating the report. */
    BST_update_report(&bst_report, bst_root);
  }
  file = fopen(filename, "r");
  if (file) {
    avl_report = report_create();
    report_clock_start(&avl_report);
    while (fscanf(file, "%d", &value) != EOF) {
      AVL_insert(&avl_report, &avl_root, value, value);
    }
    report_clock_stop(&avl_report);
    fclose(file); /* Close the stream before updating the report. */
    AVL_update_report(&avl_report, avl_root);
  }
}

void query_values(char *filename) { printf("Querying from %s\n", filename); }

void remove_values(char *filename) { printf("Removing from %s\n", filename); }

static void print_report(Report report) {
  printf("Time: %ld ms\n", report.time);
  printf("Nodes: %ld\n", report.nodes);
  printf("Height: %ld\n", report.height);
  printf("Factor: %ld\n", report.factor);
  printf("Comparisons: %ld\n", report.comparisons);
  printf("Rotations: %ld\n", report.rotations);
}

void statistics(void) {
  printf("Statistics for BST:\n");
  print_report(bst_report);
  printf("Statistics for AVL:\n");
  print_report(avl_report);
}

void execute_instructions(char *filename) {
  /* See roteiro.txt to understand the format. */
  /* Parse the file pointed to by filename, calling the functions above. */
}

int main(int argc, char **argv) {
  /* Should have a valid report at all times. */
  avl_report = report_create();
  bst_report = report_create();
  BST_initialize(&bst_root);
  AVL_initialize(&avl_root);
  insert_values("input/n1000.txt");
  statistics();
  if (argc < 2) {
    printf("Pass a filename to the program.\n");
  } else if (argc == 2) {
    execute_instructions(argv[1]);
  } else {
    printf("Pass just a filename to the program.\n");
  }
  BST_free(&bst_root);
  AVL_free(&avl_root);
  return 0;
}
