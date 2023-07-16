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
	int child_status;
	pid_t result;

	// alternatively, we can use posix_spawnp without specifying the pathname. e.g. {"echo", "hello", "world", 0}
	if (0 != posix_spawn(&result, args[0], NULL, NULL, args, environ)) {
		perror("spawn failed");
		exit(1);
	}
	waitpid(result, &child_status, 0);
	printf("pid: %d status: %d\n", result, child_status);
}