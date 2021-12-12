#ifndef ANALYSIS_FUNCTIONS_HEADER_FILE
#define ANALYSIS_FUNCTIONS_HEADER_FILE

#include "analysis.h"

void get_execution_id(char *fileName, char *buffer);
void set_execution_id(char *fileName, char *buffer);
TDL get_process_data(TDL tdl, char *process_name);
void set_cpu_time(TDL *node_adress, char *target, int value);

#endif