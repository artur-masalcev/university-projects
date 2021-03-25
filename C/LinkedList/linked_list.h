#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdio.h>

struct Node{
    int value;
    struct Node *next;
    struct Node *prev;
};

/*
Descritiption: creates a NULL doubly circular linked list
Arguments: Node **root - double reference to the head node of the list
*/
void list_create(struct Node **root);

/*
Descritiption: puts an element to the end of a doubly circualar linked list
Arguments: Node **root - double reference to the head node of the list, int val - element which needs to be placed
*/
void list_push_end(struct Node **root, int val);

/*
Descritiption: prints the values of a doubly circular linked list starting with the first element, if the
    list is empty - prints following message
Arguments: Node *root - reference to the head node of the list
*/
void list_traversal_forward(struct Node *root);

/*
Descritiption: puts an element to the begining of a doubly circualar linked list
Arguments: Node **root - double reference to the head node of the list, int val - element which needs to be placed
*/
void list_push_begining(struct Node **root, int val);

/*
Descritiption: prints the values of a doubly circular linked list starting with the last element, if the
    list is empty - prints following message
Arguments: Node *root - reference to the head node of the list
*/
void list_traversal_backward(struct Node *root);

/*
Descritiption: deletes all the elements of the doubly circualar linked list
Arguments: Node **root - double reference to the head node of the list
*/
void list_clear(struct Node **root);

/*
Description: puts an element before the particular element of the doubly circular linked list, if the element does not exists,
    prints the following message
Arguments: Node **root - double reference to the head node of the list, int target - the existing element before which the new element
    will be placed, int val - the new element
Output: 1 - the element was succesully placed in the list, 0 - the target element does not exist
*/
int list_push_before(struct Node **root, int target, int val);

#endif
