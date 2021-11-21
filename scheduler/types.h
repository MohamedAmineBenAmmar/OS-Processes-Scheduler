#ifndef TYPES_HEADER_FILE
#define TYPES_HEADER_FILE

#include <stdlib.h>
#include <stdio.h>

// Types definition

typedef struct ProcessData
{
    char process_name[50];
    int arrival_time;
    int duration; 
    int priority;

} ProcessData;

typedef struct PLNode
{
    ProcessData pd;
    struct PLNode *next;
} PLNode;

typedef PLNode *PL;


// Ready queue
typedef struct ReadyQueueNode
{
    struct ReadyQueueNode *prev;
    PLNode *process_node_adress;
    struct ReadyQueueNode *next;
} ReadyQueueNode;

typedef struct ReadyQueue
{
    ReadyQueueNode *head;
    ReadyQueueNode *tail;
} ReadyQueue;


#endif