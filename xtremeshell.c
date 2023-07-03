#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100
#define MAX_ARGS 10
#define DELIMITER " "

static inline int execute_commands(char* args[]);

int main(int argc, char *argv[])
{
   char input[MAX_INPUT_LENGTH];
   char *args[MAX_ARGS];
   
   while (1) {
       printf("&xtremeshell&-> ");
       fgets(input, sizeof(input), stdin);
       input[strcspn(input, "\n")] = '\0'; 
       
       if (strcmp(input, "xtremeshell") == 0) {
           execute_commands(args);
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


static inline int execute_commands(char* args[]) {
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork");
        return -1;
    } else if (pid == 0) {
        execvp(args[0], args);
        perror("execpv");
        return 1;
    }
    return 0;
}
