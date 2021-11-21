#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int dynamic_menu_selection(char* dirName, int choice, int* nbf, char* selectedFileName){
   
   DIR *d;
   struct dirent *dir;
   d = opendir(dirName);

   int nbdir = 0;

   char * ptr;
   int dot = '.';

   if (d){
      if (choice == 0){
         printf("\n----- Existing Scheduling Policies -----\n");
      }

      while ((dir = readdir(d)) != NULL){
         ptr = strchr( dir->d_name, dot);
         if (ptr == NULL){
            nbdir++;

            // Used for the user algorithm selection
            if (nbdir == choice && nbdir > 0){
               // printf("\nchoice selected is %s\n", dir->d_name);
               strcpy(selectedFileName, dir->d_name);
               break;
            }
            
            // Used to display the content of the directory dynamically
            if (choice == 0){
               printf("-%d: %s\n", nbdir, dir->d_name);
            }
            
         }

         
      } 

      if (choice == 0){
         *nbf = nbdir;
         selectedFileName[0] = '\0';
      } else {
         *nbf = -1;
      }
      printf("\n");
      closedir(d);
   } else {
      printf("\n Unable to open : %s ", dirName);
      return (-1);
   }
    
   return(0);
}


int main(int argc, char **argv) {
   int n, i, choice, result, nbf;
   char selectedFileName[256];
   char path[256];
   char* full_path_with_spargs;

   
   // Init path variable
   strcpy(path, "./scheduling_policies/build/");

   // Listing the content of a directory + dynamic menu
   result = dynamic_menu_selection(path, 0, &nbf, selectedFileName);
   printf("Type the number of the scheduling policy you want to use: \n");

   if (result == 0){
      do {
         scanf("%d", &choice);
         (choice > 0 && choice <= nbf) ? (result = 1) : (printf("\nPlease try again \n"));
      } while (!(result == 1));


      // Confirm to the user the choice selected
      result = dynamic_menu_selection(path, choice, &nbf, selectedFileName);
      printf("Selected scheduling policy: %s\n", selectedFileName);

      // Concatenate the full path of the executable
      strcat(path, selectedFileName);

      // Preparing the args to be passed to the scheduling policy
      n = 0;
      for(i=1; i<argc; i++){
         n++;
         n+= strlen(argv[i]);
      }
         
      full_path_with_spargs = (char*)malloc((n + strlen(path)) * sizeof(char));
      if (full_path_with_spargs == NULL){
         printf("Memory not allocated for the path with arguments.\n");
         return -1;
      } else {
         strcpy(full_path_with_spargs, path);
         for(i=1; i<argc; i++){
            strcat(full_path_with_spargs, " ");
            strcat(full_path_with_spargs, argv[i]);
         }  

         // puts(full_path_with_spargs);
         int status = system(full_path_with_spargs);
         int exitcode = status / 256;

      }

   } else {
      printf("Error occured while listing the content of the scheduling policies, please verify you path !");
      return -1;
   }
   

   return 0;
}