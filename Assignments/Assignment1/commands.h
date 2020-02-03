#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h> 
#include <signal.h>
#include <setjmp.h>
#include <sys/time.h>
#include <sys/resource.h>

#define LINE_LENGTH 100
#define MAX_ARGS 7
#define MAX_LENGTH 20
#define MAX_PT_ENTRIES 32
#define cmd_TOK_DELIM " \t\r\n\a"

int cmd_exit();
int cmd_jobs();
int cmd_kill(char **args);
int cmd_resume(char **args);
int cmd_sleep(char **args);
int cmd_suspend(char **args);
int cmd_wait(char **args);
int getProcessTime(pid_t pid);
struct process{
    int index;
    pid_t pid;
    char commandName[LINE_LENGTH];
    char status[1];

};

extern struct process pcb[];

extern int running;


// memset(pcb,0,sizeof(pcb));