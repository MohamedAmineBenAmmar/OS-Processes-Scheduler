#ifndef MAIN_HEADER_FILE
#define MAIN_HEADER_FILE

// the entire header file file

// Types definition

typedef struct ProcessData
{
    char process_name[50];
    float arrival_time;
    int duration; // to convert to float
    int priority;

} ProcessData;

typedef struct PLNode
{
    ProcessData pd;
    struct PLNode *next;
} PLNode;

typedef PLNode *PL;

// Helper functions
void add_process(PL *pl_adr, ProcessData pd)
{
    PL ptr;

    ptr = (PL)malloc(sizeof(PLNode));
    ptr->pd = pd;
    ptr->next = *pl_adr;
    *pl_adr = ptr;
}

void print_process_data(ProcessData pd)
{
    printf("Process Data:\n");
    puts(pd.process_name);
    printf("%f", pd.arrival_time);
    printf("\n");
    printf("%d", pd.duration);
    printf("\n");
    printf("%d", pd.priority);
    printf("\n");
}

void print_process_list(PL pl)
{
    PL ptr;

    ptr = pl;
    while (ptr != NULL)
    {
        printf("\n------------------------\n");
        print_process_data(ptr->pd);
        printf("\n------------------------\n");
        ptr = ptr->next;
    }
}

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

void enqueue(ReadyQueue rq, PLNode *process_node_adress)
{
    ReadyQueueNode *ptr;

    ptr = (ReadyQueueNode *)malloc(sizeof(ReadyQueue));

    ptr->prev = NULL;
    ptr->process_node_adress = process_node_adress;
    ptr->next = rq.tail;

    rq.tail = ptr;
    if (rq.head == NULL)
    {
        rq.head = ptr;
    }
}

PLNode *dequeue(ReadyQueue rq)
{
    PLNode *pl_node_adress;
    ReadyQueueNode *ptr;

    ptr = rq.head;
    pl_node_adress = rq.head->process_node_adress;
    rq.head = rq.head->prev;
    free(ptr);

    return pl_node_adress;
}

// Global variables

#endif