/**
Abstract data type: Queue
Author: Artur Masalcev(artur.masalcev@stud.mif.vu.lt)

Overview:
This is an implementation of queue data structure using dynamic memory.
NOTICE: if you want to change default data type of queue change the typedef line bellow

Description and list of supported operations:
void queue_create(struct Queue **q, int *error_code) - create a new queue
bool queue_is_empty(struct Queue *q, int *error_code) - check if queue is empty
void queue_enqueue(struct Queue *q, int value, int *error_code) - add a new element into queue
void queue_dequeue(struct Queue *q, int *error_code) - remove the last element from queue
int queue_size(struct Queue *q, int *error_code) - get numbers of elelemnt of the given queue
void queue_remove(struct Queue *q, int *error_code) - remove queue
void queue_traverse(struct Queue *q) - print elelemt values of the given queue in STDIN

Error codes:
 0 : no errors
-1 : operating system cannot allocate memory
-2 : the given queue is not initialized
-3 : the given queue is already initialized
-4 : elelemts number in the given queue reached the defined limit
-5 : the given queue is empty

For more details check the queue.c file

Constants:
MAX_QUEUE_SIZE - defines how many elements can one queue contain
MAX_VECTORS - defines how many queues can be created

Constant values are recommended. You may change the constant values depending on your aims, hardware and operating system.

Used libraries:
<stdio.h> - used for traversing queue
<stdlib.h> - used for memory allocation
<stdbool.h> - boolean data type
*/

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

///Modify this values if you want to translate the queue_print_error() function in needed language
#define ERROR_0 "ERROR  0: operation done successfully"
#define ERROR_1 "ERROR -1: operating system cannot allocate memory"
#define ERROR_2 "ERROR -2: the given queue is not initialized"
#define ERROR_3 "ERROR -3: the given queue is already initialized"
#define ERROR_4 "ERROR -4: elelemts number in the given queue reached the defined limit"
#define ERROR_5 "ERROR -5: the given queue is empty"
#define ERROR_UNKNOWN "Unexpected error"

///Use and modify these variables to gurantee that a new element will always be created and no memory leak will occur
#define MAX_QUEUE_SIZE 5 //Maximum elements number in one queue
#define MAX_QUEUES 3 //Maximum queues number

///Change this line in order to change the data type of queue
typedef int data_type;

struct Node{
    data_type val;
    struct Node *next;
};

struct Queue{
    int size;
    struct Node *back;
    struct Node *front;
};

void queue_create(struct Queue **q, int *error_code);

bool queue_is_empty(struct Queue *q, int *error_code);

void queue_enqueue(struct Queue *q, data_type value, int *error_code);

void queue_dequeue(struct Queue *q, int *error_code);

int queue_size(struct Queue *q, int *error_code);

void queue_remove(struct Queue *q, int *error_code);

void queue_traverse(struct Queue *q, void (*print)(data_type));

bool queue_is_full(struct Queue *q, int *error_code);

void queue_print_error(int error_code);

#endif
