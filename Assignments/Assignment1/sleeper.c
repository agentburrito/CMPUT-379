#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
	if(argc < 2){
		printf("More args\n");
	}else{
		sleep(atoi(argv[2]));	
	}
	return 0;
}