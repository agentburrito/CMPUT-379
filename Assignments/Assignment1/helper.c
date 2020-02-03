#include "commands.h"
#include "helper.h"

char **splitProcess(char line[])
{
  int bufsize = 256, position = 0;
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
    token = strtok(NULL, cmd_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

int getProperTime(char *token){
  int hour,minute,second,seconds;
  sscanf(token,"%02d:%02d:%02d",&hour,&minute,&second);
  hour*=3600;
  minute*=60;
  seconds=hour+minute+second;
  return seconds;
}

int getProcessTime(pid_t pid) {
  FILE *ps = popen("ps -f", "r"); // run ps
  char buffer[256];
  int num;
    
  while (fgets(buffer, sizeof(buffer), ps) != NULL) {
    // printf("%s \n",buffer);
    char **temp= splitProcess(buffer);
    if(sscanf(temp[1],"%d",&num) && num ==pid) {
      printf("%s \n",buffer);
      int time = getProperTime(temp[5]);
      pclose(ps);
      free(temp);
      return time;
    }
    memset(buffer, 0, sizeof(*buffer));
    free(temp);
  }
  pclose(ps);
  return -1; // return -1 indicate not found
}

void refresh(){
  for(int i=0;i<MAX_PT_ENTRIES;i++){
      if(pcb[i].pid!=-1){
        //Wait for any child processes to complete, return otherwise. 
        waitpid(pcb[i].pid, NULL, WNOHANG);
        int runtime = getProcessTime(pcb[i].pid);
        if(runtime == -1){
          pcb[i].index=i;
          pcb[i].pid=-1;
          strcpy(pcb[i].commandName,"EMPTY");
          strcpy(pcb[i].status,"N");
          running--;            
        }
      }
  }
}

/**
   @brief Read a line of input from stdin.
   @return The line from stdin.
 */
char *readInput(void)
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

/**
   @brief Split a line into tokens (very naively).
   @param line The line.
   @return Null-terminated array of tokens.
 */
char **splitInput(char *line)
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
