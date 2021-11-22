#include "../../scheduler/scheduler_functions.h"
#include "../../file_manager/file_manager_functions.h"

#include <string.h>

PLNode* sjp(ReadyQueue *rq){
    ReadyQueueNode *rqn_ptr;
    ReadyQueueNode *process_to_run;
    PLNode * result;
    
    process_to_run = rq->tail;
    rqn_ptr = rq->tail->next;
    while (rqn_ptr != NULL)
    {
        if (rqn_ptr->process_node_adress->pd.duration < process_to_run->process_node_adress->pd.duration){
            process_to_run = rqn_ptr;
        }
        rqn_ptr = rqn_ptr->next;
    }
    
    result = process_to_run->process_node_adress;

    // Check if the process to run is at the begenning or end of the ready queue
    if (process_to_run->next == NULL){
        rq->head = rq->head->prev;
    }

    if (process_to_run->prev == NULL){
        rq->tail = rq->tail->next;
    }

    if (process_to_run->next != NULL && process_to_run->prev != NULL){
        process_to_run->prev->next = process_to_run->next;
        process_to_run->next->prev = process_to_run->prev;
    }

    //free(process_to_run);

    return result;
} 


void sjf(PL pl){
    ReadyQueue rq;
    PLNode *ptr;
    ReadyQueueNode *test;
    PLNode *current_running_process;
    int process_arrival_time;
    int n;

    int timer;

    // Init the ready queue
    rq.head = NULL;
    rq.tail = NULL;

    // Init the pointer used to loop through the linked list
    ptr = pl;

    // Init the ready queue by the elemnts wich will be used later     
    enqueue(&rq, ptr);
    process_arrival_time = ptr->pd.arrival_time;

    
    ptr = ptr->next;
    while (ptr != NULL)
    {
        if (ptr->pd.arrival_time == process_arrival_time){
            enqueue(&rq, ptr);
            ptr = ptr->next;
        } else {
            break;
        }
    }
    
    n = 0;
    while (!(isEmptyQueue(rq) == 1))
    {
        current_running_process = sjp(&rq);
        if (n == 0){
            // Init the timer
            timer = current_running_process->pd.arrival_time;
            n++;
        }
        
        if (current_running_process->pd.arrival_time>timer){
            printf("The CPU was empty from %d to %d\n", timer, current_running_process->pd.arrival_time);
            timer = current_running_process->pd.arrival_time;
        } else if (timer > current_running_process->pd.arrival_time) {
            printf("The process was in the ready queue from the moment he wanted the CPU at %d to %d the moment when the CPU is empty\n", current_running_process->pd.arrival_time, timer);
        }
        timer+= current_running_process->pd.duration;

        while (ptr != NULL)
        {
            if (ptr->pd.arrival_time <= timer){
                enqueue(&rq, ptr);
                ptr = ptr->next;
            } else {
                // Test if the ready queue is empty
                if (isEmptyQueue(rq) == 1) {
                    enqueue(&rq, ptr);
                    ptr = ptr->next;
                }
                break;
            }
        }

        // Displaying the result 
        printf("The process: %s ran from %d with a duration of %d and left the cpu at %d\n", current_running_process->pd.process_name, current_running_process->pd.arrival_time, current_running_process->pd.duration, timer);

        // Display the state of the ready queue
        // ... to do


    }
    

}



int main(int argc, char **argv)
{
    PL pl;
    pl = parse_file(argv[1]);
    pl_sort(pl);
    // print_process_list(pl);
    sjf(pl);
    return 0;
}