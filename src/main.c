#include "AVL.h"
#include "BST.h"
#include "report.h"
#include <stdio.h>
#include <stdlib.h>

#define CODE_SIZE 8
#define NAME_SIZE 512

static Report bst_report;
static BST *bst_root = NULL;

static Report avl_report;
static AVL *avl_root = NULL;

void print_open_failure(char *filename) {
  printf("Could not open \"%s\"!\n", filename);
}

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
  } else {
    print_open_failure(filename);
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
  } else {
    print_open_failure(filename);
  }
}

void query_values(char *filename) {
  FILE *file;
  int value;
  printf("Querying from %s\n", filename);
  file = fopen(filename, "r");
  if (file) {
    bst_report = report_create();
    report_clock_start(&bst_report);
    while (fscanf(file, "%d", &value) != EOF) {
      BST_get(&bst_report, bst_root, value);
    }
    report_clock_stop(&bst_report);
    fclose(file); /* Close the stream before updating the report. */
    BST_update_report(&bst_report, bst_root);
  } else {
    print_open_failure(filename);
  }
  file = fopen(filename, "r");
  if (file) {
    avl_report = report_create();
    report_clock_start(&avl_report);
    while (fscanf(file, "%d", &value) != EOF) {
      AVL_get(&avl_report, avl_root, value);
    }
    report_clock_stop(&avl_report);
    fclose(file); /* Close the stream before updating the report. */
    AVL_update_report(&avl_report, avl_root);
  } else {
    print_open_failure(filename);
  }
}

void remove_values(char *filename) {
  FILE *file;
  int value;
  printf("Removing from %s\n", filename);
  file = fopen(filename, "r");
  if (file) {
    bst_report = report_create();
    report_clock_start(&bst_report);
    while (fscanf(file, "%d", &value) != EOF) {
      BST_remove(&bst_report, &bst_root, value);
    }
    report_clock_stop(&bst_report);
    fclose(file); /* Close the stream before updating the report. */
    BST_update_report(&bst_report, bst_root);
  } else {
    print_open_failure(filename);
  }
  file = fopen(filename, "r");
  if (file) {
    avl_report = report_create();
    report_clock_start(&avl_report);
    while (fscanf(file, "%d", &value) != EOF) {
      AVL_remove(&avl_report, &avl_root, value);
    }
    report_clock_stop(&avl_report);
    fclose(file); /* Close the stream before updating the report. */
    AVL_update_report(&avl_report, avl_root);
  } else {
    print_open_failure(filename);
  }
}

static void print_report(Report report) {
  printf("  Time: %ld ms\n", report.time);
  printf("  Nodes: %ld\n", report.nodes);
  printf("  Height: %ld\n", report.height);
  printf("  Factor: %ld\n", report.factor);
  printf("  Comparisons: %ld\n", report.comparisons);
  printf("  Rotations: %ld\n", report.rotations);
}

void statistics(void) {
  printf(" Statistics for BST:\n");
  print_report(bst_report);
  printf(" Statistics for AVL:\n");
  print_report(avl_report);
}

void execute_instructions(char *filename) {
  /* See roteiro.txt to understand the format. */
  /* Parse the file pointed to by filename, calling the functions above. */
  FILE *file = fopen(filename, "r");
  char code[CODE_SIZE];
  char name[NAME_SIZE];
  char c;
  int r;
  if (file == NULL) {
    printf("Error opening the file.\n");
    return;
  }
  while (!feof(file)) {
    /* %c is not straightforward as %s. */
    r = fscanf(file, "%s", code);
    if (r == 0 || r == EOF) {
      break;
    }
    c = *code;
    if (c == 'E') {
      statistics();
    } else if (c == 'C' || c == 'I' || c == 'R') {
      r = fscanf(file, "%s", name);
      if (r == 0 || r == EOF) {
        break;
      }
      if (c == 'C') {
        query_values(name);
      } else if (c == 'I') {
        insert_values(name);
      } else {
        remove_values(name);
      }
    }
  }
  fclose(file);
}

int main(int argc, char **argv) {
  /* Should have a valid report at all times. */
  avl_report = report_create();
  bst_report = report_create();
  if (argc < 2) {
    printf("Pass a filename to the program.\n");
    return 0;
  }
  if (argc > 2) {
    printf("Pass just a filename to the program.\n");
    return 0;
  }
  BST_initialize(&bst_root);
  AVL_initialize(&avl_root);
  execute_instructions(argv[1]);
  BST_free(&bst_root);
  AVL_free(&avl_root);
  return 0;
}
