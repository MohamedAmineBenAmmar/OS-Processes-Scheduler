#include "../../scheduler/scheduler_functions.h"
#include "../../file_manager/file_manager_functions.h"
#include "shared/priority_functions.h"


void dynamic_priority(PL pl, char *priority){
    ReadyQueue rq;
    PLNode *ptr;
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
    timer = ptr->pd.arrival_time;

    
    ptr = ptr->next;
    while (ptr != NULL)
    {
        if (ptr->pd.arrival_time == timer){
            enqueue(&rq, ptr);
            ptr = ptr->next;
        } else {
            break;
        }
    }

    n = 0;
    while (!(isEmptyQueue(rq) == 1))
    {
        current_running_process = get_process_with_priority(&rq, priority);
        // The current running process is going to run for a certain amount of time
        // until a process with more priority come and take his palace



        if (current_running_process->pd.arrival_time > timer){
            printf("The CPU was empty from %d to %d\n", timer, current_running_process->pd.arrival_time);
            timer = current_running_process->pd.arrival_time;
        } else if (timer >= current_running_process->pd.arrival_time && n == 1) {
            printf("The process: %s was in the ready queue from the moment he wanted the CPU at %d to %d the moment when the CPU is empty\n", current_running_process->pd.process_name,current_running_process->pd.arrival_time, timer);
        }
/*
        (n == 0) ?
        (printf("The process: %s ran from %d with a duration of %d and left the cpu at %d\n", current_running_process->pd.process_name, current_running_process->pd.arrival_time, current_running_process->pd.duration, current_running_process->pd.arrival_time + current_running_process->pd.duration))
        :
        (printf("The process: %s ran from %d with a duration of %d and left the cpu at %d\n", current_running_process->pd.process_name, timer, current_running_process->pd.duration, timer + current_running_process->pd.duration));
*/
        printf("The process: %s ran from %d with a priority equal to %d and left the cpu at %d\n", current_running_process->pd.process_name, timer, current_running_process->pd.priority, timer + current_running_process->pd.duration);        
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

        (n == 0) && (n++);
        // Display the state of the ready queue
        // ... to do


    }
    

}



int main(int argc, char **argv)
{
    PL pl;
    char priority[5];
    strcpy(priority, "ASC");
    
    pl = parse_file(argv[1]);
    pl_sort(pl);
    // print_process_list(pl);
    dynamic_priority(pl, priority);
    return 0;
}