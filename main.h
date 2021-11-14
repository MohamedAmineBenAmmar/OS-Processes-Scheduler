#ifndef MAIN_HEADER_FILE
#define MAIN_HEADER_FILE

#include <ctype.h>

// the entire header file file

// Types definition

typedef struct ProcessData {
   char process_name[50];
   float arrival_time;   
   int duration;
   int priority;

} ProcessData;


typedef struct PLLNode
{
    ProcessData pd;
    struct PLLNode* next;
} PLLNode;


typedef PLLNode*  PLL;


// Helper functions
void add_process(PLL* pl_adr, ProcessData pd){
    PLL ptr;

    ptr = (PLL)malloc(sizeof(PLLNode));
    ptr->pd = pd;
    ptr->next = *pl_adr;
    *pl_adr = ptr;
}


void print_process_data(ProcessData pd){
    printf("Process Data:\n");
    puts(pd.process_name);
    printf("%f", pd.arrival_time);
    printf("\n");
    printf("%d", pd.duration);
    printf("\n");
    printf("%d", pd.priority);
    printf("\n");

}

void print_process_linked_list(PLL pl){
    PLL ptr;

    ptr = pl;
    while (ptr != NULL){
        printf("\n------------------------\n");
        print_process_data(ptr->pd);
        printf("\n------------------------\n");
        ptr = ptr->next;
    }
}


void substr(char *s, int a, int b, char *t) 
{
    strncpy(t, s+a, b);
}


// Global variables
int test;


#endif