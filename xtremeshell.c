#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cmdexecution.h"

#define MAX_INPUT_LENGTH 100
#define MAX_ARGS 100
#define DELIMITER " "

int main(int argc, char *argv[])
{
   char input[MAX_INPUT_LENGTH];
   char *args[MAX_ARGS];
   
   const char* path = getenv("PATH");
   char new_path[1024];
   snprintf(new_path, sizeof(new_path), "PATH=%s", path);
   putenv(new_path);   
   bool running = true;
   
   while (running) {
       printf("\033[32m&xtremeshell$ -> ");
       fgets(input, sizeof(input), stdin);
       input[strcspn(input, "\n")] = '\0'; 
       
       if (strcmp(input, "xtremeshell") == 0) {
           execute_commands(args);
           continue;
       }
       
       int argcount = 0;
       char *token = strtok(input, DELIMITER);
       while (token != NULL && argcount < MAX_ARGS) {
           args[argcount] = token;
           argcount++;
           token = strtok(NULL, DELIMITER); 
       }
       args[argcount] = NULL; 
       execute_commands(args);
   }
}