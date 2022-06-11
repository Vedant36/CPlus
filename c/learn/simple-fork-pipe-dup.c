// simple fork-pipe-dup example
#include <stdio.h>
#include <stdlib.h>         // standard library definitions
#include <unistd.h>         // all system calls
#include <errno.h>          // error reporting
#include <sys/types.h>      // type pid_t
#include <string.h>

int main()
{
	int fd[2];
	// create a pipe
	if (pipe(fd) == -1) {
		perror("pipe");
		exit(errno);
	}
	pid_t p = fork();
	if (p == -1) {
		perror("pipe");
		exit(errno);
	}

	if (p == 0) {
		printf("[Debug] Child  with forkid: %d; pid: %d\n",
				p, getpid());
		close(fd[0]);
		dup2(fd[1], 1);
		execlp("echo", "echo", "-n",
				"'Do' or 'do not', there is no 'try'", NULL);
	} else {
		printf("[Debug] Parent with forkid: %d; pid: %d\n",
				p, getpid());
		close(fd[1]);
		char buf[64];
		int count = read(fd[0], buf, 64);
		if (count <= 0) {
			perror("read");
			exit(errno);
		}
		buf[count] = '\0';
		printf("Read %d bytes `%s` from file descriptor:%d\n",
				count, buf, fd[1]);
		close(fd[0]);
	}

	return 0;
}
