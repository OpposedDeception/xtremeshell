#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static inline int execute_commands(char* args[]) __attribute__((always_inline));

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
        snprintf(cmd, sizeof(cmd), "wget %s", args[1]);
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
            snprintf(command, strlen(args[0]) + 2, "/%s", args[0]);
            execl("/bin/sh", "sh", "-c", command, NULL);
            perror("execl");
            free(command);
            return 1;
        }
        execvp(args[0], args);
        perror("execvp");
        return 1;
    } else {
        int status;
        waitpid(pid, &status, 0);
        return 0;
    }
    return 0;
}