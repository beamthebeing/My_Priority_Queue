//
//  priority_queue.c
//  daily8
//
//  Created by Dylan Bennett on 4/21/19.
//  Copyright © 2019 Dylan Bennett. All rights reserved.
//

#include "priority_queue.h"
#include <stdio.h>
#include <stdlib.h>

struct queue
{
    int index_of_front;
    int index_of_entry;
    int size;
    int capacity;
    int* data;
    int* priority;
};
typedef struct queue Priority_Queue;

PRIORITY_QUEUE priority_queue_init_default(void)
{
    Priority_Queue* pQ;
    pQ = (Priority_Queue*)malloc(sizeof(Priority_Queue));
    if (pQ != NULL)
    {
        pQ->size = 0;
        pQ->capacity = 7;
        pQ->index_of_entry = 0;
        pQ->index_of_front = 0;
        pQ->data = malloc(sizeof(int)*pQ->capacity);
        if (pQ->data == NULL)
        {
            free(pQ);
            return NULL;
        }
        pQ->priority = malloc(sizeof(int)*pQ->capacity);
        if (pQ->priority == NULL)
        {
            free(pQ);
            return NULL;
        }
    }
    return (PRIORITY_QUEUE)pQ;
}

Status priority_queue_insert(PRIORITY_QUEUE hQueue, int priority_level, int data_item)
{
    Priority_Queue* pQ = (Priority_Queue*)hQueue;
    int* pData_Temp;
    int* pPriority_Temp;
    int i;
    int j;
    int index_of_parent = -1;
    int index_hold;
    int data_temp;
    int priority_temp;
    
    if (pQ->size >= pQ->capacity) //not enough room so resize
    {
        pData_Temp = malloc(sizeof(int) * pQ->capacity * 2);
        if (pData_Temp == NULL)
        {
            return FAILURE;
        }
        pPriority_Temp = malloc(sizeof(int) * pQ->capacity * 2);
        if (pPriority_Temp == NULL)
        {
            return FAILURE;
        }
        for (i = 0, j=pQ->index_of_front; i < pQ->size; i++)
        {
            pData_Temp[i] = pQ->data[j];
            pPriority_Temp[i] = pQ->priority[j];
            j = (j + 1)%pQ->capacity;
        }
        free(pQ->data);
        free(pQ->priority);
        pQ->data = pData_Temp;
        pQ->priority = pPriority_Temp;
        pQ->capacity *= 2;
        pQ->index_of_front = 0;
        pQ->index_of_entry = pQ->size;
    }
    
    pQ->data[pQ->index_of_entry] = data_item;
    pQ->priority[pQ->index_of_entry] = priority_level;
    
    //call fix up
    index_hold = pQ->index_of_entry; //Temp variable to hold pQ->index_of_entry, since it gets changed in while loop
    while (pQ->index_of_entry > 0)
    {
        index_of_parent = (pQ->index_of_entry - 1) / 2;

        if(pQ->priority[pQ->index_of_entry] > pQ->priority[index_of_parent])
        {
            
            //call my_swap
            data_temp = pQ->data[pQ->index_of_entry];
            pQ->data[pQ->index_of_entry] = pQ->data[index_of_parent];
            pQ->data[index_of_parent] = data_temp;
            
            priority_temp = pQ->priority[pQ->index_of_entry];
            pQ->priority[pQ->index_of_entry] = pQ->priority[index_of_parent];
            pQ->priority[index_of_parent] = priority_temp;
        }
        //reassign index of entry till it equals 0
        pQ->index_of_entry = index_of_parent;
    }
    
    pQ->index_of_entry = (index_hold + 1) % pQ->capacity;
    pQ->size++;
    
    return SUCCESS;
}

Status priority_queue_service(PRIORITY_QUEUE hQueue)
{
    Priority_Queue* pQ = (Priority_Queue*)hQueue;
    int data_temp;
    int priority_temp;
    int index_hold = pQ->index_of_front;
    int index_of_left_child = -1;
    int index_of_right_child = -1;
    int index_of_largest_child = -1;
    
    if (pQ->size <= 0)
    {
        return FAILURE;
    }
    
    //call my swap
    data_temp = pQ->data[0];
    pQ->data[0] = pQ->data[pQ->size - 1];
    pQ->data[pQ->size - 1] = data_temp;

    priority_temp = pQ->priority[0];
    pQ->priority[0] = pQ->priority[pQ->size - 1];
    pQ->priority[pQ->size - 1] = priority_temp;
    

    //Call fix down
    index_of_left_child = 2*pQ->index_of_front + 1;
    index_of_right_child = 2*pQ->index_of_front + 2;
    while(index_of_right_child < pQ->size - 1 || index_of_left_child < pQ->size - 1)
    {
        if (index_of_right_child < pQ->size - 1) // have two children
        {
            index_of_largest_child =
            pQ->priority[index_of_left_child] > pQ->priority[index_of_right_child] ?
            index_of_left_child : index_of_right_child;

            if(pQ->priority[pQ->index_of_front] < pQ->priority[index_of_largest_child])
            {
                //call my_swap
                data_temp = pQ->data[pQ->index_of_front];
                pQ->data[pQ->index_of_front] = pQ->data[index_of_largest_child];
                pQ->data[index_of_largest_child] = data_temp;

                priority_temp = pQ->priority[pQ->index_of_front];
                pQ->priority[pQ->index_of_front] = pQ->priority[index_of_largest_child];
                pQ->priority[index_of_largest_child] = priority_temp;
            }
        }
        
        else if (index_of_left_child < pQ->size - 1) //have only left child
        {
            index_of_largest_child = index_of_left_child;
            if(pQ->priority[pQ->index_of_front] < pQ->priority[index_of_largest_child])
            {
                //Call my_swap
                data_temp = pQ->data[pQ->index_of_front];
                pQ->data[pQ->index_of_front] = pQ->data[index_of_largest_child];
                pQ->data[index_of_largest_child] = data_temp;

                priority_temp = pQ->priority[pQ->index_of_front];
                pQ->priority[pQ->index_of_front] = pQ->priority[index_of_largest_child];
                pQ->priority[index_of_largest_child] = priority_temp;
            }
        }
        pQ->index_of_front = index_of_largest_child;
        index_of_left_child = 2*pQ->index_of_front + 1;
        index_of_right_child = 2*pQ->index_of_front + 2;
    }
    
    pQ->index_of_front = index_hold;
    pQ->size--;
    return SUCCESS;
}



int priority_queue_front(PRIORITY_QUEUE hQueue, Status* pStatus)
{
    Priority_Queue* pQ = (Priority_Queue*)hQueue;
    if (pQ->size <= 0)
    {
        if (pStatus != NULL)
        {
            *pStatus = FAILURE;
        }
        return -1337;
    }
    
    if (pStatus != NULL)
    {
        *pStatus = SUCCESS;
    }
    return pQ->data[pQ->index_of_front];
}

Boolean priority_queue_is_empty(PRIORITY_QUEUE hQueue)
{
    Priority_Queue* pQ = (Priority_Queue*)hQueue;
    
    return (Boolean)(pQ->size <= 0);
}

void priority_queue_destroy(PRIORITY_QUEUE* phQueue)
{
    Priority_Queue* pQ = (Priority_Queue*)*phQueue;
    free(pQ->data);
    free(pQ->priority);
    free(pQ);
    *phQueue = NULL;
}

