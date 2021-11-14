#ifndef MAIN_HEADER_FILE
#define MAIN_HEADER_FILE


// the entire header file file

// Types definition

typedef struct ProcessData {
   char process_name[50];
   float arrival_time;   
   int duration;
   int priority;

} ProcessData;


typedef struct PDLLNode
{
    struct PDLLNode* prev;
    ProcessData pd;
    struct PDLLNode* next;
} PDLLNode;


typedef struct PDLL
{
    PDLLNode* head;
    PDLLNode* tail;
} PDLL;


// Helper functions
void add_process(PDLL* pl_adr, ProcessData pd){
    PDLLNode* ptr;

    ptr = (PDLLNode*)malloc(sizeof(PDLLNode));
    ptr->prev = NULL;
    ptr->pd = pd;
    ptr->next = (*pl_adr).head;
    (*pl_adr).head = ptr;
    if ((*pl_adr).tail == NULL) {
        (*pl_adr).tail = ptr;
    }
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

void print_process_list(PDLL pl){
    PDLLNode* ptr;

    ptr = pl.head;
    while (ptr != NULL){
        printf("\n------------------------\n");
        print_process_data(ptr->pd);
        printf("\n------------------------\n");
        ptr = ptr->next;
    }
}


// Global variables

#endif