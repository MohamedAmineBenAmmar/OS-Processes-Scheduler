#include <stdio.h>
#include <string.h>
#include <dirent.h>

int dynamic_menu_selection(char* dirName, int choice){
   
   DIR *d;
   struct dirent *dir;
   d = opendir(dirName);

   int nbdir = 0;

   char * ptr;
   int dot = '.';

   if (d){
      while ((dir = readdir(d)) != NULL){
         ptr = strchr( dir->d_name, dot);
         if (ptr == NULL){
            nbdir++;

            // Used for the user algorithm selection
            if (nbdir == choice && nbdir > 0){
               printf("choice selected is %s\n", dir->d_name);
            }
            
            // Used to display the content of the directory dynamically
            if (choice == 0){
               printf("%s\n", dir->d_name);
            }
            
         }

         
      } 
      
      closedir(d);
   } else {
      printf("\n Unable to open : %s ", dirName);
      return (-1);
   }
    
   return(0);
}

void scheduling_policy_selection(){

}


int main() {
   // printf() displays the string inside quotation
   dynamic_menu_selection("./scheduling_policies/build", 1);
   return 0;
}