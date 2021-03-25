//Artur Masalcev//
//LT
//Sudaryti ciklinį dvipusį sąrašą. Parašyti procedūrą kuri įterpia prieš reikšme nurodytą elementą naują elementą.
//Jeigu tokio elemento nėra, turi būti išvestas atitinkamas pranešimas.

//EN
//Create looped doubly linked listed. Design a procedure, that inserts the new value before particular existing one.
//Print the required message if the element does not exist

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

int main(){
    struct Node *list;
    list_create(&list);

    int elements_count; //Represents the amount of elements in the linked list
    printf("How many elements will present in the linked list? ");
    scanf("%d", &elements_count);

    int element; //Represents the value of the element that will be placed in the list
    int argument; //Variable which is needed for user input

    //Fill the list with elements//
    for(int i = 0; i < elements_count; i++){
        printf("Enter the element: ");
        scanf("%d", &element);

        printf("Push in the begining '1' or in the end '2' of the list? ");
        scanf("%d", &argument);

        if(argument == 1)list_push_begining(&list, element);
        else if(argument == 2)list_push_end(&list, element);
        printf("\n");
    }

    //Print list//
    printf("Would you like the list to be printed from the begining '1' or from the end '2'\n");
    scanf("%d", &argument);

    if(argument == 1)list_traversal_forward(list);
    else if(argument == 2)list_traversal_backward(list);

    //Insert a new element before extisting one//
    printf("Enter the element: ");
    scanf("%d", &element);

    printf("Enter before which element [%d] should be placed ", element);
    printf("if the target element does not exist, it won't be put: ");

    scanf("%d", &argument);
    if(list_push_before(&list, argument, element) == 1){
        printf("The element [%d] was successfully placed in the list\n", argument);
    }
    else{
        printf("Element [%d] is not found\n", argument);
    }

    //Print list//
    printf("Would you like the list to be printed from the begining '1' or from the end '2'\n");
    scanf("%d", &argument);

    if(argument == 1)list_traversal_forward(list);
    else if(argument == 2)list_traversal_backward(list);

    list_clear(&list);
    return 0;
}
