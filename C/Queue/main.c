///  Project: Abstract data structure. Queue
///  Author: Artur Masalcev. Software Engineering Group 4

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

void print(int arg){
    printf("%d",arg);
}

int main(){
    int error_code; //Variable for keeping error codes
    int arg_1 = 0; //Primary argument for user input used for choosing menu actions
    int arg_2 = 0; //Secondary argument for user input used as a parameter for additional functions

    void (*print_ptr)(int) = &print; //pointer to a print function for queue traversal

    struct Queue *queues[MAX_QUEUES] = {NULL};
    int current_pos = 0;

    int queues_count = 0;

    bool is_queue_chosen = false;

    while(true){
        printf("Please, choose what action would you like to perform: \n");
        printf("[1] - create empty queue\n");
        printf("[2] - switch queue\n");
        printf("[3] - add new element(enqueue)\n");
        printf("[4] - delete the first element(dequeue)\n");
        printf("[5] - check whether the queue is empty\n");
        printf("[6] - print the number of elements in the queue\n");
        printf("[7] - print all elements of the queue\n");
        printf("[8] - remove queue\n");
        printf("[9] - check if queue is full\n");
        printf("[0] - destroy all queues and exit the program\n");

        scanf("%d", &arg_1);
        system("cls");

        if(arg_1 == 1){
            if(queues_count != MAX_QUEUES){
                for(int i = 0; i < MAX_QUEUES; ++i){
                    if(queues[i] == NULL){
                        queue_create(&queues[i], &error_code);
                        if(error_code != 0)printf("Error occured please try again or reset the program\n");
                        else printf("Successfully created new queue with index %d\n", i + 1);
                        if(queues_count == 0){
                            current_pos = i;
                            printf("Automatically switched to queue %d\n", i + 1);
                            is_queue_chosen = true;
                        }
                        ++queues_count;
                        break;
                    }
                }
            }
            else printf("You have reached the maximum number of queues, you have to remove some of the current ones\n");
            printf("\n");
        }
        else if(arg_1 == 2){
            if(queues_count == 0)printf("There are no created queues yet, use [1] operation to create one\n");
            else{
                printf("Which queue would you like to choose? (1 - 5)\n");
                printf("Currently existing queues: \n");

                for(int i = 0; i < MAX_QUEUES; ++i){
                    if(queues[i] != NULL)printf("queue %d\n", i + 1);
                }

                scanf("%d", &arg_2);
                system("cls");

                if(arg_2 - 1 < MAX_QUEUES && arg_2 - 1 >= 0 && queues[arg_2 - 1] != NULL){
                    current_pos = arg_2 - 1;
                    printf("Successfully switched to queue number %d\n", arg_2);
                    is_queue_chosen = true;
                }
                else printf("Cannot switch to queue number %d\n", arg_2);
            }
            printf("\n");
        }
        else if(arg_1 == 3){
            if(queues_count == 0)printf("There are no created queues yet, use [1] operation to create one\n");
            else if(!is_queue_chosen)printf("Please choose the queue with [2] operation\n");
            else{
                printf("What value would you like to insert: ");
                scanf("%d", &arg_2);
                queue_enqueue(queues[current_pos], arg_2, &error_code);
                if(error_code == 0) printf("Value (%d) inserted successfully\n", arg_2);
                else queue_print_error(error_code);
            }
            printf("\n");
        }
        else if(arg_1 == 4){
            if(queues_count == 0)printf("There are no created queues yet, use [1] operation to create one\n");
            else if(!is_queue_chosen)printf("Please choose the queue with [2] operation\n");
            else{
                queue_dequeue(queues[current_pos], &error_code);
                if(error_code == 0) printf("Element deleted successfully\n");
                else queue_print_error(error_code);
            }
            printf("\n");
        }
        else if(arg_1 == 5){
            if(queues_count == 0)printf("There are no created queues yet, use [1] operation to create one\n");
            else if(!is_queue_chosen)printf("Please choose the queue with [2] operation\n");
            else{
                bool ans = queue_is_empty(queues[current_pos], &error_code);
                if(error_code != 0)queue_print_error(error_code);
                else{
                    if(ans)printf("The queue is empty\n");
                    else printf("The queue is not empty\n");
                }
            }

            printf("\n");
        }
        else if(arg_1 == 6){
            if(queues_count == 0)printf("There are no created queues yet, use [1] operation to create one\n");
            else if(!is_queue_chosen)printf("Please choose the queue with [2] operation\n");
            else{
                int ans = queue_size(queues[current_pos], &error_code);
                if(error_code == -2)printf(ERROR_2, error_code);
                else printf("Number of elements: %d\n", ans);
            }

            printf("\n");
        }
        else if(arg_1 == 7){
            if(queues_count == 0)printf("There are no created queues yet, use [1] operation to create one\n");
            else if(!is_queue_chosen)printf("Please choose the queue with [2] operation\n");
            else{
                queue_traverse(queues[current_pos], print);
            }
            printf("\n");
        }
        else if(arg_1 == 8){
            if(queues_count == 0)printf("There are no created queues yet, use [1] operation to create one\n");
            else if(!is_queue_chosen)printf("Please choose the queue with [2] operation\n");
            else{
                queue_remove(queues[current_pos], &error_code);
                if(error_code != 0)queue_print_error(error_code);
                else{
                    printf("Queue deleted successfully\n");
                    queues[current_pos] = NULL;
                    --queues_count;
                    is_queue_chosen = false;
                }
            }
            printf("\n");
        }
        else if(arg_1 == 9){
            if(queues_count == 0)printf("There are no created queues yet, use [1] operation to create one\n");
            else{
                bool result = queue_is_full(queues[current_pos], &error_code);
                if(error_code == 0){
                    if(result)printf("The queue is full\n");
                    else printf("The queue is not full\n");
                }
                else queue_print_error(error_code);
            }
            printf("\n");
        }
        else if(arg_1 == 0)break;
        else printf("INVALID INPUT\n");
    }

    for(int i = 0; i < MAX_QUEUES; ++i)queue_remove(queues[current_pos], &error_code);

    return 0;
}
