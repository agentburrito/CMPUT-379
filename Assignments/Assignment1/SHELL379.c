#include "commands.h"

#define LINE_LENGTH 100
#define MAX_ARGS 7
#define MAX_LENGTH 20
#define MAX_PT_ENTRIES 32



struct process pcb[MAX_PT_ENTRIES];
int index=0;


/*
  Function Declarations for builtin shell commands:
 */



/*
  List of builtin commands, followed by their corresponding functions.
 */


/**
  @brief Launch a program and wait for it to terminate.
  @param args Null terminated list of arguments (including program).
  @return Always returns 1, to continue execution.
 */
int cmd_launch(char **args)
{
  pid_t pid, wpid;
  int status;

  if(sizeof(args)==sizeof(char*)&&args[0]==0){
    return 1;
  }

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("cmd");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("cmd");
  } else {
    // Parent process
    do {
      struct process p;
      pcb[index]=p;
      p.index=index;
      p.pid=pid;
      strcpy(p.commandName,*args);
      p.status=status;
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

#define cmd_RL_BUFSIZE 1024
/**
   @brief Read a line of input from stdin.
   @return The line from stdin.
 */
char *cmd_read_line(void)
{
  int bufsize = LINE_LENGTH;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "cmd: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Read a character
    c = getchar();

    // If we hit EOF, replace it with a null character and return.
    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, free buffer and return garbage data
    if (position >= bufsize) {
      free(buffer);
      char *garbage = malloc(sizeof(char*));
      garbage[0]=0;
      return garbage;
    }
  }
}

#define cmd_TOK_BUFSIZE 64
#define cmd_TOK_DELIM " \t\r\n\a"
/**
   @brief Split a line into tokens (very naively).
   @param line The line.
   @return Null-terminated array of tokens.
 */
char **cmd_split_line(char *line)
{
  int bufsize = MAX_ARGS*MAX_LENGTH, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "cmd: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, cmd_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position > MAX_ARGS) {
      free(tokens);
      free(token);
      char **garbage = malloc(sizeof(char*));
      garbage[0]=0;
      return garbage;

    }

    token = strtok(NULL, cmd_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
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
  do {
    printf("SHELL379: ");
    line = cmd_read_line();
    if(sizeof(line)==sizeof(char*)&&line[0]==0){
      printf("Arguments too long, max length = 100\n");
      free(line);
      continue;
    }
    else{
      args = cmd_split_line(line);
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
  cmd_loop();

  // Perform any shutdown/cleanup.

  return EXIT_SUCCESS;
}
