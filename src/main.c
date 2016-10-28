#include <stdio.h>

#include "AVL.h"
#include "BST.h"

void insert_values(char *filename) { printf("Inserting from %s\n", filename); }

void query_values(char *filename) { printf("Querying from %s\n", filename); }

void remove_values(char *filename) { printf("Removing from %s\n", filename); }

void statistics(void) { printf("Printing statistics\n"); }

void execute_instructions(char *filename) {
  /* See roteiro.txt to understand the format. */
  /* Parse the file pointed to by filename, calling the functions above. */
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Pass a filename to the program.\n");
  } else if (argc == 2) {
    execute_instructions(argv[1]);
  } else {
    printf("Pass just a filename to the program.\n");
  }
  return 0;
}
