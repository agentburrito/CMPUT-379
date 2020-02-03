#include "commands.h"
#include "helper.h"

struct process pcb[MAX_PT_ENTRIES];

int running = 0;



int cmd_launch(char **args)
{
  pid_t pid, wpid;
  int status;

  if(sizeof(args)==sizeof(char*)&&args[0]==0){
    return 1;
  }

  //if(strcmp(args[sizeof(args)/sizeof(args[0]))
  for(int i =0;i<sizeof(args);i++){
    printf("%s    %d\n",args[i],args[i]);
  }

  pid = fork();
  if (pid == 0) {
    // Child process
   
    if (execvp(args[0], args) == -1) {
      perror("cmd");
    }
    else{
      printf("%d    \n",status);
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("cmd");
  } else {
    // Parent process
    for(int i=0;i<MAX_PT_ENTRIES;i++){
      if(pcb[i].pid==-1){
        struct process p;
        p.index=i;
        p.pid=pid;
        strcpy(p.commandName,*args);
        strcpy(p.status,"R");
        pcb[i]=p;
        running++;
        break;
      }
    }
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

/**
   @brief Execute shell built-in or launch program.
   @param args Null terminated list of arguments.
   @return 1 if the shell should continue running, 0 if it should terminate
 */
int cmd_execute(char **args)
{
  if (args[0] == NULL) {
    // An empty command was entered.
  
    return 1;
  }
  //Arguments are too long
  for(int i=0;i<sizeof(args);i++){
    // printf("%s\n",args[i]);
    if(sizeof(args[i]) > MAX_ARGS){
      printf("Argument too long, max length = 20\n");
      return 1;
    }
  }

  if (strcmp(args[0], "exit") == 0) {
      return (cmd_exit());
  }
  else if (strcmp(args[0], "jobs") == 0) {
      return (cmd_jobs());
  }
  else if (strcmp(args[0], "kill") == 0) {
      return (cmd_kill(args));
  }
  else if (strcmp(args[0], "resume") == 0) {
      return (cmd_resume(args));
  }
  else if (strcmp(args[0], "sleep") == 0) {
      return (cmd_sleep(args));
  }
  else if (strcmp(args[0], "suspend") == 0) {
      return (cmd_suspend(args));
  }
  else if (strcmp(args[0], "wait") == 0) {
      return (cmd_wait(args));
  }
  

  return cmd_launch(args);
}


/**
   @brief Loop getting input and executing it.
 */
void cmd_loop(void)
{
  char *line;
  char **args;
  int status;
  fflush(stdout);
  fflush(stdin);
  refresh();
  do {
    printf("SHELL379: ");
    line = readInput();
    if(sizeof(line)==sizeof(char*)&&line[0]==0){
      printf("Arguments too long, max length = 100\n");
      free(line);
      continue;
    }
    else{
      args = splitInput(line);
      if(sizeof(args)==sizeof(char*)&&args[0]==0){
        printf("Too many arguments, maximum = 7\n");
        free(line);
        free(args);
        continue;
      }
      else{
        status = cmd_execute(args);
        free(line);
        free(args);
      }
    }
  } while (status);
}

/**
   @brief Main entry point.
   @param argc Argument count.
   @param argv Argument vector.
   @return status code
 */
int main(int argc, char **argv)
{
  // Load config files, if any.

  // Run command loop.

	// if( setjmp( Restart_Looping ) < 0 ) {
	// 	perror( "Failed setjmp" );
	// 	exit( -1 );
	// }

  for (int i=0;i<MAX_PT_ENTRIES;i++){
    pcb[i].index=i;
    pcb[i].pid=-1;
    strcpy(pcb[i].commandName,"EMPTY");
    strcpy(pcb[i].status,"N");
  }
  
  cmd_loop();

  // Perform any shutdown/cleanup.

  return EXIT_SUCCESS;
}



