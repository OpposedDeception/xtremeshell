#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 100
#define MAX_ARGS 100
#define DELIMITER " "

static inline int execute_commands(char* args[]);

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

static inline int execute_commands(char* args[]) {
    if (args[0] == NULL) {
        return 0;
    }
    
    if (strcmp(args[0], "cd") == 0) {
        if (chdir(args[1]) != 0) {
            perror("chdir");
            return -1;
        }
        return 0;
    }
    
    if (strcmp(args[0], "uname") == 0 && strcmp(args[1], "-a") == 0) {
        system("uname -a");
        return 0;
    }
    
    if (strcmp(args[0], "wget") == 0 && args[1] != NULL) {
        char cmd[100];
        sprintf(cmd, sizeof(cmd), "wget %s", args[1]);
        system(cmd);
    }
    
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return -1;
    } else if (pid == 0) {
        if (args[0][0] == '\0') {
            char* command = (char*)malloc(strlen(args[0]) + 2);
            if (command == NULL) {
                perror("malloc");
                return -1;
            }
            sprintf(command, "/%s", args[0]);
            execl("/bin/sh", "sh", "-c", command, NULL);
            perror("execl");
            free(command);
            return 1;
        }
        execvp(args[0], args);
        perror("execvp");
        return 1;
    }
    return 0;
}