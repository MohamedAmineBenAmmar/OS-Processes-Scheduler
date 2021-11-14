#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"



int verify_line(char* line){
    // A line is going to be skipped in the floowing cases

}


ProcessData extract_process_data(char* line){
    char field[50];
    int n = 0;
    ProcessData pd;

    for (int i = 0; i < strlen(line); i++)
    {
        if (line[i] != ',' && line[i] != '\n' && line[i]!= '\0') {
            strncat(field, &line[i], 1);
        } else {
            switch (n)
            {
            case 0:
                // printf("process name\n");
                strcpy(pd.process_name,  field); 
                break;

            case 1:
                // printf("Arrival time\n");
                pd.arrival_time = atof(field);
                break;

            case 2:
                // printf("Duration\n");
                pd.duration = atoi(field);
                break;

            case 3:
                // printf("Priority\n");
                pd.priority = atoi(field);
                break;
            
            default:
                break;
            }

            n++;
            field[0] = '\0';

        }
        
    }

    // print_process_data(pd);
    return pd;
    
}

int parse_file(char* fileName, PDLL* pl_adr) {
    FILE* file = fopen(fileName, "r"); /* should check the result */
    char line[256];

    ProcessData pd;
    
    if(!file){
        printf("\n Unable to open : %s ", fileName);
        return (-1);
    }

    // Init the process linked list
    (*pl_adr).head = NULL;
    (*pl_adr).tail = NULL;

    while (fgets(line, sizeof(line), file)) {       
        // Skip comments and empty lines
        // Extract the process data
        pd = extract_process_data(line);
        add_process(pl_adr, pd);
    }
    

    fclose(file);

    return 0;
}

void pl_mergesort(PDLL* pl_adr, int a, int b){
    
}

int main(int argc, char* argv[])
{
    // char const* const fileName = argv[1]; /* should check that argc > 1 */

    char* fileName = "tests/config/config2";
    PDLL pl;
    int res;

    printf("test \n");
    res = parse_file(fileName, &pl);
    print_process_list(pl);
    

    return 0;
}