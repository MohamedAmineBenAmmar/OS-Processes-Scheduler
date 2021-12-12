#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "analysis_functions.h"

void get_execution_id(char *fileName, char *buffer)
{
    FILE *file = fopen(fileName, "r"); /* should check the result */

    if (!file)
    {
        printf("\n Unable to open : %s ", fileName);
    }

    fgets(buffer, sizeof(buffer), file);
    fclose(file);
}

void set_execution_id(char *fileName, char *buffer)
{
    FILE *file = fopen(fileName, "w"); /* should check the result */

    if (!file)
    {
        printf("\n Unable to open : %s ", fileName);
    }

    fputs(buffer, file);
    fclose(file);
}

TDL get_process_data(TDL tdl, char *process_name)
{
    TDL ptr;
    TDL res;

    res = NULL;
    ptr = tdl;
    while (ptr != NULL)
    {
        if (strcmp(ptr->process_name, process_name) == 0)
        {
            res = ptr;
            break;
        }
    }

    return res;
}

void set_cpu_time(TDL *node_adress, char *target, int value)
{
    CPU_Time_List ptr;
    CPU_Time_List new_cpu_time_ptr;
    if (strcmp(target, "IN") == 0)
    {
        ptr = (*node_adress)->entry_cpu_time;
        if (ptr == NULL)
        {
            (*node_adress)->entry_cpu_time = (CPU_Time_Node *)malloc(sizeof(CPU_Time_Node));
            (*node_adress)->entry_cpu_time->time = value;
            (*node_adress)->entry_cpu_time->next = NULL;
        }
        else
        {
            while (ptr->next != NULL)
            {
                ptr = ptr->next;
            }

            new_cpu_time_ptr = (CPU_Time_Node *)malloc(sizeof(CPU_Time_Node));
            new_cpu_time_ptr->time = value;
            new_cpu_time_ptr->next = NULL;

            ptr->next = new_cpu_time_ptr;
        }
    }
    else
    {
        ptr = (*node_adress)->exit_cpu_time;
        if (ptr == NULL)
        {
            (*node_adress)->exit_cpu_time = (CPU_Time_Node *)malloc(sizeof(CPU_Time_Node));
            (*node_adress)->exit_cpu_time->time = value;
            (*node_adress)->exit_cpu_time->next = NULL;
        }
        else
        {
            while (ptr->next != NULL)
            {
                ptr = ptr->next;
            }

            new_cpu_time_ptr = (CPU_Time_Node *)malloc(sizeof(CPU_Time_Node));
            new_cpu_time_ptr->time = value;
            new_cpu_time_ptr->next = NULL;

            ptr->next = new_cpu_time_ptr;
        }
    }
}

/*
int main()
{

    char line[256];
    char test[26];

    strcpy(test, "4444");
    get_execution_id("analysis/config", line);
    printf("\n1- %s\n", line);
    set_execution_id("analysis/config", test);
    get_execution_id("analysis/config", line);
    printf("\n2- %s\n", line);
}
*/