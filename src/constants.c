#include <stdio.h>

#include "constants.h"

/**
 * Writes a textual representation of the specified Element to standard output.
 */
void print_element(Element element) { printf("%d", element); }

/**
 * Compares two elements and returns true if the first is strictly less than
 * the second.
 */
int element_less_than(Element left, Element right) { return left < right; }

/**
 * Compares two elements and returns true if they are equal.
 */
int element_equals(Element left, Element right) {
  /* Defined in terms of element_less_than to reduce refactoring overhead. */
  return !element_less_than(left, right) && !element_less_than(right, left);
}

/**
 * Returns a hash for the specified Element.
 *
 * If element_equals(a, b), then element_hash(a) == element_hash(b).
 */
int element_hash(Element element) { return element; }

/**
 * Writes a textual representation of the specified key to standard output.
 */
void print_key(Key key) { printf("%d", key); }

/**
 * Compares two keys and returns true if the first is strictly less than the
 * second.
 */
int key_less_than(Key left, Key right) { return left < right; }

/**
 * Compares two keys and returns true if they are equal.
 */
int key_equals(Key left, Key right) {
  /* Defined in terms of element_less_than to reduce refactoring overhead. */
  return !element_less_than(left, right) && !element_less_than(right, left);
}
