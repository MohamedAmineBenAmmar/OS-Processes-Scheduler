#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char **argv)
{
    int n, i;
    char path[256];
    char *full_path_with_spargs;

    // Init path variable
    strcpy(path, "./scheduling_policies/build/PROG");

    // Preparing the args to be passed to the scheduling policy
    n = 0;
    for (i = 1; i < argc; i++)
    {
        n++;
        n += strlen(argv[i]);
    }

    full_path_with_spargs = (char *)malloc((n + strlen(path)) * sizeof(char));
    if (full_path_with_spargs == NULL)
    {
        printf("Memory not allocated.\n");
        return -1;
    }
    else
    {
        strcpy(full_path_with_spargs, path);
        for (i = 1; i < argc; i++)
        {
            strcat(full_path_with_spargs, " ");
            strcat(full_path_with_spargs, argv[i]);
        }

        printf("\nThe value of n is equal to = %d\n", strlen(full_path_with_spargs));
        puts(full_path_with_spargs);
        int status = system(full_path_with_spargs);
    }

return 0;
}