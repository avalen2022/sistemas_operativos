#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
	int i, status;
	pid_t pid;

	if (argc == 1) {
		printf("usage: pinger ip/name [ip/name ...]\n");
		exit(EXIT_FAILURE);
	}

	for (i = 1; i < argc; i++) {
		pid = fork();
		if (pid < 0) {
			fprintf(stderr, "Err: Didnt fork\n");
			exit(EXIT_FAILURE);
		} else if (pid == 0) {
			execl("/bin/ping", "ping", "-c", "1", "-W", "5",
			      argv[i], NULL);
		}
	}

	for (i = 1; i < argc; i++) {
		wait(&status);

		if (status != 0) {
			fprintf(stderr, "Err: Cant do the ping\n");
			exit(EXIT_FAILURE);
		}
	}

	exit(EXIT_SUCCESS);
}
