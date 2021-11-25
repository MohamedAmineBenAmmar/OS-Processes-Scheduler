#include "../../scheduler/scheduler_functions.h"
#include "../../file_manager/file_manager_functions.h"


void round_robin(PL pl, int quantum){
    ReadyQueue rq;
    PLNode *ptr;
    PLNode *current_running_process;
    int timer, old_timer, flag;

    // Init the ready queue
    rq.head = NULL;
    rq.tail = NULL;

    // Init the pointer used to loop through the linked list
    ptr = pl;
 
    // Init the current running process
    enqueue(&rq, ptr);
    timer = ptr->pd.arrival_time;
    ptr = ptr->next;

    int n;
    n = 0;

    while (!(ptr == NULL && isEmptyQueue(rq) == 1))
    {
        current_running_process = dequeue(&rq);

        // Here I consider that the process will finish its execution
        flag = 1;
        
        // Calculating when the process will finish its execution
        // timer represents when the currnet running process will finis its execution

        if (current_running_process->pd.arrival_time > timer){
            printf("The CPU was empty from %d to %d\n", timer, current_running_process->pd.arrival_time);
            timer = current_running_process->pd.arrival_time;
        } else if (timer >= current_running_process->pd.arrival_time && n == 1) {
            printf("The process: %s was in the ready queue from the moment he wanted the CPU at %d to %d the moment when the CPU is empty\n", current_running_process->pd.process_name, current_running_process->pd.arrival_time, timer);
        }

        if (quantum < current_running_process->pd.duration){
            // Saving the old of value timer in a tmp variable
            old_timer = timer;

            // Calculating the new duration of the process
            current_running_process->pd.duration = current_running_process->pd.duration - quantum;

            // Updating the value of timer
            timer+= quantum;

            // Calculating the new arrival time of a process
            current_running_process->pd.arrival_time = timer;

            // Mean that the current running process wants more processor time
            flag = 0;

            
            printf("The process %s ran during 1 quantum, from %d to %d, the new duration is equal to = %d and the new arrival time is = %d\n", current_running_process->pd.process_name, old_timer, timer, current_running_process->pd.duration, current_running_process->pd.arrival_time);
        } else {
            old_timer = timer;
            timer+= current_running_process->pd.duration;
            printf("The process %s ran during %d CPU unit, from %d to %d. The process finish its execution.\n", current_running_process->pd.process_name, current_running_process->pd.duration,old_timer, timer);
        }

        while (ptr != NULL)
        {
            if (ptr->pd.arrival_time <= timer){
                enqueue(&rq, ptr);
                ptr = ptr->next;

                if (flag == 0) {
                    // Enqueue the current running process after the new coming pocesses
                    enqueue(&rq, current_running_process);
                }
            } else {
                if (flag == 0){
                    enqueue(&rq, current_running_process);
                }

                // Test if the ready queue is empty
                if (isEmptyQueue(rq) == 1) {
                    enqueue(&rq, ptr);
                    ptr = ptr->next;
                }
                break;
            }
        }

        // Check if the last process didn't finish its execution
        if (ptr == NULL){
            if (flag == 0){
                enqueue(&rq, current_running_process);
            }
        }

        // Increment he value of n to test if the process if the 1st one or not
        (n == 0) && (n++);
        
        // Display the state of the ready queue
        // ... to do
        
    }

}



int main(int argc, char **argv)
{
    PL pl;
    pl = parse_file(argv[1]);
    pl_sort(pl);
    int quantum;

    quantum = 4;
    // print_process_list(pl);
    round_robin(pl, quantum);
    return 0;
}