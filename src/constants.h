#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <limits.h>

/**
 * An Element used when we need to express the absence of an element.
 *
 * This is good enough as the aim of this project is didactic. However, a
 * pointer to NULL would be a better alternative.
 */
#define NULL_ELEMENT INT_MIN

/**
 * The type used as keys in maps and trees.
 */
typedef int Key;

/**
 * The type the structures will store.
 */
typedef int Element;

/**
 * Writes a textual representation of the specified Element to standard output.
 */
void print_element(Element element);

/**
 * Compares two elements and returns true if the first is strictly less than
 * the second.
 */
int element_less_than(Element left, Element right);

/**
 * Compares two elements and returns true if they are equal.
 */
int element_equals(Element left, Element right);

/**
 * Returns a hash for the specified Element.
 *
 * If element_equals(a, b), then element_hash(a) == element_hash(b).
 */
int element_hash(Element element);

/**
 * Writes a textual representation of the specified key to standard output.
 */
void print_key(Key key);

/**
 * Compares two keys and returns true if the first is strictly less than the
 * second.
 */
int key_less_than(Key left, Key right);

/**
 * Compares two keys and returns true if they are equal.
 */
int key_equals(Key left, Key right);

#endif
