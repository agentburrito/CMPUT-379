#include "commands.h"

/*
  Builtin function implementations.
*/

/**
   @brief Bultin command: change directory.
   @param args List of args.  args[0] is "cd".  args[1] is the directory.
   @return Always returns 1, to continue executing.
 */
// int cmd_cd(char **args)
// {
//   if (args[1] == NULL) {
//     fprintf(stderr, "cmd: expected argument to \"cd\"\n");
//   } else {
//     if (chdir(args[1]) != 0) {
//       perror("cmd");
//     }
//   }
//   return 1;
// }

/**
   @brief Builtin command: print help.
   @param args List of args.  Not examined.
   @return Always returns 1, to continue executing.
 */
// int cmd_help(char **args)
// {
//   int i;
//   printf("Stephen Brennan's cmd\n");
//   printf("Type program names and arguments, and hit enter.\n");
//   printf("The following are built in:\n");

//   for (i = 0; i < cmd_num_builtins(); i++) {
//     printf("  %s\n", builtin_str[i]);
//   }

//   printf("Use the man command for information on other programs.\n");
//   return 1;
// }

/**
   @brief Builtin command: exit.
   @param args List of args.  Not examined.
   @return Always returns 0, to terminate execution.
 */
int cmd_exit(char **args)
{
  return 0;
}

int cmd_jobs(char **args){
    printf("Testing jobs\n");
    return 1;
}

int cmd_kill(char **args){
    if(args[1]==NULL || sizeof(args[1])!=sizeof(int)){
        printf("You must enter a valid amount to sleep for\n");
        return 1;
    }
    else{
        sleep((int) args[1]);
    }
    return 1;
}


int cmd_resume(char **args){
    if(args[1]==NULL || sizeof(args[1])!=sizeof(int)){
        printf("You must enter a valid amount to sleep for\n");
        return 1;
    }
    else{
        sleep((int) args[1]);
    }
    return 1;
}

int cmd_sleep(char **args){
    int num;
    printf("%s   \n",args[1]);
    if(args[1]==NULL){
        printf("You must enter an amount to sleep for\n");
        return 1;
    }

    for(int i=0;i<sizeof(args[1]);i++){
        if(args[1][i]>57||(args[1][i]<48 && args[1][i]!=0)){
            printf("%d\n",args[1][i]);
            // printf("You must enter a valid amount to sleep for\n");
            // return 1;
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
    if(args[1]==NULL || sizeof(args[1])!=sizeof(int)){
        printf("You must enter a valid amount to sleep for\n");
        return 1;
    }
    else{
        sleep((int) args[1]);
    }
    return 1;
}

int cmd_wait(char **args){
    if(args[1]==NULL || sizeof(args[1])!=sizeof(int)){
        printf("You must enter a valid amount to sleep for\n");
        return 1;
    }
    else{
        sleep((int) args[1]);
    }
    return 1;
}