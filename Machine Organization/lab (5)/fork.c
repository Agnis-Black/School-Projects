#include <spawn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// external symbol that always points to the list of enviornment variables
extern char **environ;

int main(int argc, char **argv) {
	char *args[4] = {"/bin/echo", "hello", "world", 0};
	int child_status, result;
	printf("%s\n",environ[0]);
	result = fork();
	if (result < 0) {
		perror("fork failed");
		exit(1);
	}
	if (result == 0) {
		// alternatively, we can use execvp without specifying the pathname. e.g. {"echo", "hello", "world", 0}
		execv(args[0], args);
		// if we get to this line we know something went wrong...
		perror("execv failed");
		exit(1);
	}
	else {
		wait(&child_status);
	}
	printf("status: %d\n", child_status);
        //getpid();
}
