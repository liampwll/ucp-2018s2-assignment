/*
 * FILE:     linkedlist.h
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Simple linked list.
 * LAST MOD: 2018-10-18
 */

#include "linkedlist.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

/** Node of a list. */
struct Node
{
    /** Previous node of the list, or the node contained in a LinkedList
     * struct if this is the first node in a list. */
    Node *prev;
    /** Data provided by user. */
    void *data;
    /** Previous node of the list, or the node contained in a LinkedList
     * struct if this is the last node in a list. */
    Node *next;
};

struct LinkedList
{
    /** Length of the list. */
    size_t len;
    /** Node used to detect the start and end of the list, does not contain
     * data provided by the user and does not count towards the length of the
     * list. */
    Node head;
};

/**
 * @brief Get the a node from a linked list.
 *
 * @param list The list to get the node from.
 * @param index The index of the node to get.
 *
 * @return The node, or NULL if the index is out of range.
 */
static Node *getNode(LinkedList *list, size_t index);

LinkedList *linkedListCreate(void)
{
    LinkedList *list;

    list = (LinkedList *)malloc(sizeof(LinkedList));
    if (list != NULL)
    {
        list->len = 0;
        list->head.next = &list->head;
        list->head.prev = &list->head;
    }

    return list;
}

void linkedListDestroy(LinkedList *list)
{
    Node *node;
    Node *next;

    if (list != NULL)
    {
        node = list->head.next;
        while (node != &list->head)
        {
            next = node->next;
            free(node);
            node = next;
        }
    }

    free(list);
}

size_t linkedListLength(LinkedList *list)
{
    return list->len;
}

void *linkedListGet(LinkedList *list, size_t index)
{
    struct Node *node;

    assert(list != NULL);

    node = getNode(list, index);
    return node == NULL ? NULL : node->data;
}

void *linkedListPop(LinkedList *list, size_t index)
{
    void *data;
    Node *node;

    assert(list != NULL);

    node = getNode(list, index);
    if (node == NULL)
    {
        data = NULL;
    }
    else
    {
        assert(node != &list->head);
        data = node->data;
        node->next->prev = node->prev;
        node->prev->next = node->next;
        free(node);

        --list->len;
    }

    return data;
}

int linkedListInsert(LinkedList *list, size_t index, void *item)
{
    int retval = 0;
    Node *node;
    Node *newNode;

    assert(list != NULL);

    /* Special case for last element */
    node = index == list->len ? &list->head : getNode(list, index);
    if (node == NULL)
    {
        retval = -1;
    }

    if (retval == 0)
    {
        newNode = (Node *)malloc(sizeof(Node));
        if (newNode == NULL)
        {
            retval = -1;
        }
    }

    if (retval == 0)
    {
        newNode->data = item;
        newNode->next = node;
        newNode->prev = node->prev;

        node->prev->next = newNode;
        node->prev = newNode;

        ++list->len;
    }

    return retval;
}

static Node *getNode(LinkedList *list, size_t index)
{
    Node *node;
    size_t i;

    assert(list != NULL);

    if (index >= list->len)
    {
        node = NULL;
    }
    else
    {
        node = list->head.next;
        i = 0;
        for (i = 0; i < index; ++i)
        {
            node = node->next;
        }
    }

    return node;
}
