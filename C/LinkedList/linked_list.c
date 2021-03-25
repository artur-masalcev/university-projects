#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

void list_create(struct Node **root){
    *root = NULL;
}

void list_push_end(struct Node **root, int val){
    if(*root == NULL){ //If the list is empty
        struct Node *new_element = (struct Node *)malloc(sizeof (struct Node));

        new_element->value = val;
        new_element->next = new_element;
        new_element->prev = new_element;

        *root = new_element;
    }
    else{
        struct Node *ptr = *root; //Pointer which is needed to modify elements of the list, currently points to the head
        struct Node *new_element = (struct Node *)malloc(sizeof (struct Node));

        new_element->value = val;
        new_element->next = *root;
        new_element->prev = ptr->prev;

        ptr->prev = new_element;

        while(ptr->next != *root){ //Set the pointer to the last element before head
            ptr = ptr->next;
        }

        ptr->next = new_element;
    }
}

void list_traversal_forward(struct Node *root){
    struct Node *ptr = root; //Pointer which is needed to modify elements of the list, currently points to the head

    if(ptr == NULL)printf("The list is currently empty.\n"); //If the list is empty print following message
    else{
        printf("Elements from the begining: %d", ptr->value); //Prints the first element

        //Printing elements from the second to the last//
        ptr = ptr->next;
        while(ptr != root){
            printf(" %d", ptr->value);
            ptr = ptr->next;
        }

        printf("\n");
    }
}

void list_push_begining(struct Node **root, int val){
    if(*root == NULL){ //If the list is empty
        //Putting the element as the first element of the list//
        struct Node *new_element = (struct Node *)malloc(sizeof (struct Node));

        new_element->value = val;
        new_element->next = new_element;
        new_element->prev = new_element;

        *root = new_element;
    }
    else{
         struct Node *new_element = (struct Node *)malloc(sizeof (struct Node));
         struct Node *ptr = *root; //Pointer which is needed to modify elements of the list, currently points to the head

         ptr = ptr->prev;
         ptr->next = new_element;
         ptr = *root;

         new_element->value = val;
         new_element->next = *root;
         new_element->prev = ptr->prev;

         ptr->prev = new_element;

         *root = new_element;
    }
}

void list_traversal_backward(struct Node *root){
    if(root == NULL)printf("The list is currently empty"); //If the list is empty print the following message
    else{
        struct Node *ptr = root->prev; //Pointer which is needed to modify elements of the list, currently points to the last element
        printf("Elements in the reverse order: %d", ptr->value); //Print the last element

        //Print the elements starting with the penultimate element and finishing with the head
        ptr = ptr->prev;
        while(ptr != root->prev){
            printf(" %d", ptr->value);
            ptr = ptr->prev;
        }
    }
}

void list_clear(struct Node **root){
    if(*root == NULL)return;

    struct Node *current = *root; //Pointer which refers to the element which will be deleted
    struct Node *next; //Pointer which refers to the element that goes after the current element

    //Cycling through the list and deleting the elements starting with second and finishing with the head//
    current = current->next;

    while(current->next != *root){
        next = current->next;
        free(current);
        current = next;
    }

    *root = NULL;
}

int list_push_before(struct Node **root, int target, int val){
    struct Node *ptr = *root; //Pointer which is needed to modify elements of the list, currently points to the head

    if(*root == NULL){ //If the list is empty
        return 0;
    }
    else if(ptr->value == target){
        list_push_begining(root, val); //If the element matches the head value, the algorithm is similair to placing it in the begining
    }
    else{
        //Search for the target element starting with the second element//
        ptr = ptr->next;
        while(ptr->value != target && ptr != *root)ptr = ptr->next;
        if(ptr == *root){ //If the pointer made a loop it means that the element does not exist
            return 0;
        }

        //Placing the new element//
        struct Node *new_element = (struct Node *)malloc(sizeof (struct Node));
        new_element->value = val;
        new_element->next = ptr;
        new_element->prev = ptr->prev;

        struct Node *ptr_2 = ptr->prev; //Pointer which is needed to connect the new_element and the that will go before it
        ptr->prev = new_element;
        ptr_2->next = new_element;

        return 1;
    }
}
