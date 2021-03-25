#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <stdbool.h>

void queue_create(struct Queue **q, int *error_code){
    /**
        Description:
        Initializes a new queue with no elements

        Example of usage:
        struct Queue *queue = NULL;
        queue_create(&queue);

        Error codes:
         0 : initialized successfully
        -1 : operating system cannot allocate memory
        -3 : the given queue is already initialized
    */
    struct Queue *new_queue = (struct Queue *)malloc(sizeof(struct Queue));

    if(new_queue == NULL){
        //Return error if memory cannot be allocated
        *error_code = -1;
        return;
    }

    new_queue->front = NULL;
    new_queue->back = NULL;
    new_queue->size = 0;

    if(*q == NULL){
        *q = new_queue;
        *error_code = 0;
        return;
    }
    else{
        //Return error if queue is alredy initialized
        *error_code = -3;
        return;
    }
}

bool queue_is_empty(struct Queue *q, int *error_code){
    /**
        Description:
        Checks whether the queue is empty

        Error codes:
         0 : no errors
        -2 : the given queue is not initialized

        Return values:
        true : queue is empty (size equals to zero)
        false: queue is not empty (size is greater than zero), or error occured(check error_code)
    */

    if(q == NULL){
        //Return error if queue is not initialized
        *error_code = -2;
        return false;
    }

    *error_code = 0;
    if(q->size == 0) return true;
    else return false;
}

void queue_enqueue(struct Queue *q, data_type value, int *error_code){
    /**
        Description:
        Inserts the new value into the queue

        Error codes:
         0 : the value added successfully
        -1 : operating system cannot allocate memory
        -2 : the given queue is not initialized
        -4 : elelemts number in the given queue reached the defined limit
    */

    if(q == NULL){
        //Return error if the queue is not initialized
        *error_code = -2;
        return;
    }

    struct Node *new_element = (struct Node *)malloc(sizeof(struct Node));

    if(new_element == NULL){
        //Return error if memory cannot be allocated
        *error_code = -1;
        return;
    }

    if(q->size == MAX_QUEUE_SIZE){
        //return error if elements number limit is reached
        *error_code = -4;
        return;
    }

    new_element->val = value;

    if(q->size == 0){
        new_element->next = NULL;
        q->front = new_element;
        q->back = new_element;
        ++q->size;
    }
    else{
        new_element->next = NULL;
        q->back->next = new_element;
        q->back = q->back->next;
        ++q->size;
    }

    *error_code = 0;
}

void queue_dequeue(struct Queue *q, int *error_code){
    /**
        Description:
        Deletes the first element of the given queue

        Error codes:
         0 : deleted successfully
        -2 : the given queue is not initialized
        -5 : the given queue is empty
    */
    if(q == NULL){
        *error_code = -2;
        return;
    }
    if(q->size == 0){
        *error_code = -5;
        return;
    }
    else{
        struct Node *ptr = q->front;
        q->front = q->front->next;
        free(ptr);
        q->size--;
    }
    *error_code = 0;
}

int queue_size(struct Queue *q, int *error_code){
    /**
        Description:
        Returns the number of elements in the given queue

        Return values:
        -1 if error occured
        Otherwise, number of elements in the given queue

        Error codes:
          0 : no errors
         -2 : the queue is not initialized
    */

    if(q == NULL){
        *error_code = -2;
        return -1;
    }
    else{
        *error_code = 0;
        return q->size;
    }
}

void queue_remove(struct Queue *q, int *error_code){
    /**
        Description:
        Deletes all elements of the given queue, as well as the queue itself

        Return values:
        0  : deleted successfully
        -2 : the given queue is not initialized
    */

    if(q == NULL){
        //Return error if the queue is not initialized
        *error_code = -2;
        return;
    }

    while(q->front != NULL)queue_dequeue(q, error_code);
    q = NULL; //Setting q to NULL, because deleteing it using stdlib.h free() doesn't change the value of *q
    free(q);

    *error_code = 0;
}

void queue_traverse(struct Queue *q, void (*print)(data_type)){
    /**
        Description:
        Prints elements of the given queue. This function handles both unitialized and empty queues cases.

        Warning:
        In order to use this function user need to create void(*print)(data_type) function, where data_type stands for
            currently used data type.

        For example, this is a function for int data type:

        void print(int arg){printf("%d", arg);}

    */

    if(q == NULL){
        printf("The given queue is not initialized\n");
        return;
    }
    if(q->size == 0){
        printf("The given queue is empty\n");
        return;
    }

    struct Node *ptr = q->front;
    printf("Current queue: ");

    while(ptr != NULL){
        print(ptr->val);
        printf(" ", ptr->val);
        ptr = ptr->next;
    }

    printf("\n");
}

bool queue_is_full(struct Queue *q, int *error_code){
    if(q == NULL){
        *error_code = -2;
        return false;
    }
    else {
        *error_code = 0;
        return q->size == MAX_QUEUE_SIZE;
    }
}

void queue_print_error(int error_code){
    switch(error_code){
        case -1:
            printf(ERROR_1);
            break;
        case -2:
            printf(ERROR_2);
            break;
        case -3:
            printf(ERROR_3);
            break;
        case -4:
            printf(ERROR_4);
            break;
        case -5:
            printf(ERROR_5);
            break;
        case 0:
            printf(ERROR_0);
            break;
        default:
            printf(ERROR_UNKNOWN);
    }
}
