#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h> 
#include <signal.h>
#include <setjmp.h>

#define LINE_LENGTH 100
#define MAX_ARGS 7
#define MAX_LENGTH 20
#define MAX_PT_ENTRIES 32

int cmd_exit();
int cmd_jobs();
int cmd_kill(char **args);
int cmd_resume(char **args);
int cmd_sleep(char **args);
int cmd_suspend(char **args);
int cmd_wait(char **args);
struct process{
    int index;
    pid_t pid;
    char commandName[LINE_LENGTH];
    int status;

};