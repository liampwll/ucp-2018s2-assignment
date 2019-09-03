/*
 * FILE:     linkedlist.h
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Simple linked list.
 * LAST MOD: 2018-10-20
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stddef.h>

/** Opaque object used by linked list functions. */
typedef struct LinkedList LinkedList;

/**
 * Create a new empty linked list.
 *
 * @return Pointer to empty linked list or NULL if an error occurs.
 */
LinkedList *linkedListCreate(void);

/**
 * Destroy a linked list. No functions can be used on a linked list after this
 * function is called on it.
 *
 * @param list The list to be destroyed.
 */
void linkedListDestroy(LinkedList *list);

/**
 * Get the length of a linked list.
 *
 * @param list The list.
 *
 * @return The number of elements in the list.
 */
size_t linkedListLength(LinkedList *list);

/**
 * Get an element from a linked list.
 *
 * @param list The list.
 * @param index Index of item to get from list.
 *
 * @return The item at the index, or NULL if the element is out of range.
 */
void *linkedListGet(LinkedList *list, size_t index);

/**
 * Remove an element from the linked list and return it.
 *
 * @param list The list.
 * @param index Index of the item to remove.
 *
 * @return The item at the index, or NULL if the element is out of range.
 */
void *linkedListPop(LinkedList *list, size_t index);

/**
 * Insert an element at the index, pushing other nodes forward.
 *
 * @param list The list.
 * @param index Index of the item to remove.
 * @param item The item to insert.
 *
 * @return Zero if the item is inserted, non-zero if the insertion fails or
 * the index is out of range.
 */
int linkedListInsert(LinkedList *list, size_t index, void *item);

#endif /* LINKEDLIST_H */
