#include "commands.h"
#include "helper.h"

/*
  Builtin function implementations.
*/


/**
   @brief Builtin command: exit.
   @param args List of args.  Not examined.
   @return Always returns 0, to terminate execution.
 */

 
int cmd_exit(char **args){
    int status;
    pid_t wpid;
    do {
      wpid = waitpid(-1, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    struct rusage usage;
    getrusage(RUSAGE_CHILDREN, &usage);
    printf("User time = %*ld seconds\nSys  time = %*ld seconds\n", 5, usage.ru_utime.tv_sec, 5, usage.ru_stime.tv_sec);
    return 0;
}

int cmd_jobs(){
    refresh();
    if (running >0){
        printf("Running processes:\n #    PID S SEC COMMAND\n");
        for(int i=0;i<MAX_PT_ENTRIES;i++){
            if(pcb[i].pid!=-1){
                int runtime = getProcessTime(pcb[i].pid);
                printf(" %d: %d %c   %d %s",pcb[i].index,pcb[i].pid,pcb[i].status,runtime,pcb[i].commandName);
            }
        }
    }
    printf("Processes = %d active\nCompleted processes: \n",running);

    // get usage
    struct rusage usage;
    getrusage(RUSAGE_CHILDREN, &usage);
    printf("User time = %*ld seconds\nSys  time = %*ld seconds\n", 5, usage.ru_utime.tv_sec, 5, usage.ru_stime.tv_sec);

    return 1;
}

int cmd_kill(char **args){
    int num;
    if(args[1]==NULL){
        printf("You must enter a pid to kill for\n");
        return 1;
    }

    for(int i=0;i<sizeof(args[1]);i++){
        if(args[1][i]>57||(args[1][i]<48 && args[1][i]!=0)){
            printf("You must enter a valid pid to kill for\n");
            return 1;
        }
    }
    
    if(sscanf(args[1],"%d",&num)){
        for(int i=0;i<MAX_PT_ENTRIES;i++){
            if(pcb[i].pid==num){
                kill(pcb[i].pid, SIGKILL);
                pcb[i].index=i;
                pcb[i].pid=-1;
                strcpy(pcb[i].commandName,"EMPTY");
                strcpy(pcb[i].status,"N");
                running--;    
            }
        }
        printf("Process not found\n");
        return 1;
    }
    else{
        printf("Error Killing\n");
        return 1;
    }
    
    return 1;
}


int cmd_resume(char **args){
    int num;
    if(args[1]==NULL){
        printf("You must enter a pid to resume\n");
        return 1;
    }

    for(int i=0;i<sizeof(args[1]);i++){
        if(args[1][i]>57||(args[1][i]<48 && args[1][i]!=0)){
            printf("You must enter a valid pid to resume\n");
            return 1;
        }
    }
    
    if(sscanf(args[1],"%d",&num)){
        for(int i=0;i<MAX_PT_ENTRIES;i++){
            if(pcb[i].pid==num){
                strcpy(pcb[i].status,"R");
                kill(pcb[i].pid, SIGCONT);
            }
        }
        printf("Process not found\n");
        return 1;
    }
    else{
        printf("Error Resuming\n");
        return 1;
    }
    
    return 1;
}


int cmd_sleep(char **args){
    int num;
    if(args[1]==NULL){
        printf("You must enter an amount to sleep for\n");
        return 1;
    }

    for(int i=0;i<sizeof(args[1]);i++){
        if(args[1][i]>57||(args[1][i]<48 && args[1][i]!=0)){
            printf("You must enter a valid amount to sleep for\n");
            return 1;
        }
    }
    
    if(sscanf(args[1],"%d",&num)){
        sleep(num);
    }
    else{
        printf("Error Sleeping\n");
        return 1;
    }
    
    return 1;
}

int cmd_suspend(char **args){
    int num;
    if(args[1]==NULL){
        printf("You must enter a pid to suspend\n");
        return 1;
    }

    for(int i=0;i<sizeof(args[1]);i++){
        if(args[1][i]>57||(args[1][i]<48 && args[1][i]!=0)){
            printf("You must enter a valid pid to suspend\n");
            return 1;
        }
    }
    
    if(sscanf(args[1],"%d",&num)){
        for(int i=0;i<MAX_PT_ENTRIES;i++){
            if(pcb[i].pid==num){
                strcpy(pcb[i].status,"S");
                kill(pcb[i].pid, SIGSTOP);
            }
        }
        printf("Process not found\n");
        return 1;
    }
    else{
        printf("Error Suspending\n");
        return 1;
    }
    
    return 1;
}

int cmd_wait(char **args){
    int num;
    if(args[1]==NULL){
        printf("You must enter an amount to suspend for\n");
        return 1;
    }

    for(int i=0;i<sizeof(args[1]);i++){
        if(args[1][i]>57||(args[1][i]<48 && args[1][i]!=0)){
            printf("You must enter a valid amount to suspend for\n");
            return 1;
        }
    }
    
    if(sscanf(args[1],"%d",&num)){
        for(int i=0;i<MAX_PT_ENTRIES;i++){
            if(pcb[i].pid==num){
                waitpid(pcb[i].pid,NULL,0);
            }
        }
        printf("Process not found\n");
        return 1;
    }
    else{
        printf("Error Sleeping\n");
        return 1;
    }
    
    return 1;
}
