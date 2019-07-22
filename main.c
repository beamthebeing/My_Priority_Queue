//
//  main.c
//  daily8
//
//  Created by Dylan Bennett on 4/21/19.
//  Copyright © 2019 Dylan Bennett. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "priority_queue.h"


void test_part_one(PRIORITY_QUEUE hQueue);
void test_part_two(PRIORITY_QUEUE hQueue);
void test_part_three(PRIORITY_QUEUE hQueue);

int main(int argc, char * argv[])
{
    PRIORITY_QUEUE hQueue;
    
    //create queue
    hQueue = priority_queue_init_default();
    if(hQueue == NULL)
    {
        printf("Failed to create Priority Queue.");
        exit(1);
    }
    
    //randomize seed
    srand((unsigned int)time(NULL));
        
    //Start Part 1 of test (Empty queue)
    test_part_one(hQueue);
    
    //Start Part 2 of test (Queue is Filled)
    test_part_two(hQueue);
    
    //Start Part 3 of test (Queue is Emptied)
    test_part_three(hQueue);

    //clear queue from memory
    priority_queue_destroy(&hQueue);
    return 0;
}



//Part 1 of test (Empty queue)
void test_part_one(PRIORITY_QUEUE hQueue)
{
    printf("\n******\n\n");
    
    //Test for is_empty
    printf("After init_default...\n\n"
           "The is_empty function evaluates as: \n\t");
    if (priority_queue_is_empty(hQueue) == TRUE)
    {
        printf("[Queue is Empty]\n");
    }
    else
    {
        printf("[Queue is NOT Empty.]\n");
    }
    printf("The data value of the front function evaluates as:\n\t[%d]\n", priority_queue_front(hQueue, NULL));
    printf("\n******\n\n");
}




//Part 2 of test (Queue is Filled)
void test_part_two(PRIORITY_QUEUE hQueue)
{
    int random;
    int i;
    Status status;
    
    //Fill the queue with random numbers
    printf("After each insert of a random number\n"
           "the front of the queue evaluates as...\n\n");
    for(i = 0; i < 10; i++)
    {
        random = rand() % 100;
        //printf("%d\n", random);
        status = priority_queue_insert(hQueue, random, random);
        if (status == FAILURE)
        {
            printf("priority_queue_insert Failed.\n");
            exit(1);
        }
        printf("%d\n", priority_queue_front(hQueue, &status));
        if (status == FAILURE)
        {
            printf("priority_queue_front returned FAILURE.\n");
            exit(1);
        }
    }
    
    //Test for is_empty
    printf("\nThe is_empty function evaluates as: \n\t");
    if (priority_queue_is_empty(hQueue) == TRUE)
    {
        printf("[Queue is Empty]\n");
    }
    else
    {
        printf("[Queue is NOT Empty.]\n");
    }
    printf("\n******\n\n");
}


//Part 3 of test (Queue is Emptied)
void test_part_three(PRIORITY_QUEUE hQueue)
{
    int i;
    Status status;
    
    //Service all elements in queue
    printf("Start service on all elements in Queue...\n"
           "Printing out the data value, which equals the priority key,\n"
           "of the front before each service.\n\n");
    for(i = 0; i < 10; i++)
    {
        printf("data_value of front = %d\n", priority_queue_front(hQueue, NULL));
        status = priority_queue_service(hQueue);
        if (status == FAILURE)
        {
            printf("priority_queue_service Failed.\n");
            exit(1);
        }
    }
    
    //Test for is_empty
    printf("\nThe is_empty function evaluates as: \n\t");
    if (priority_queue_is_empty(hQueue) == TRUE)
    {
        printf("[Queue is Empty]\n");
    }
    else
    {
        printf("[Queue is NOT Empty.]\n");
    }
    printf("The data value of the front function evaluates as:\n\t[%d]\n", priority_queue_front(hQueue, NULL));
    printf("\n******\n\n");
}
