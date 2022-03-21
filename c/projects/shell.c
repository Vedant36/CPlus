// Inclomplete
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int run_command();

int main()
{
	while(run_command()) ;
	return 0;
}

int run_command()
{
	char *cmd[16];
	char read_buf[1024];
	int read_count = read(1, read_buf, 1024);
	write(1, "$ ", 2);
	if (read_count <= 1)
		return 0;
	printf("Read: %d\n", read_count);
	int cmd_ind = 0, last_ind = 0;
	printf(">%s<\n", read_buf);
	for (int i = 0; i < read_count &&
			read_buf[i] != '\n' && read_buf[i] != '\r'; i++) {
		printf(":%d:", read_buf[i]);
		if (read_buf[i] == ' ') {
			printf("%d,%d ", cmd_ind, last_ind);
			fflush(stdout);
			cmd[cmd_ind++][i - last_ind] = '\0';
			last_ind = i;
		} else {
			printf("%d,%d ", cmd_ind, last_ind);
			fflush(stdout);
			cmd[cmd_ind][i - last_ind] = read_buf[i];
		}
	}
	cmd[cmd_ind] = NULL;
	if (strcmp(cmd[0], "exit") == 0) {
		return 0;
	}

	pid_t p = fork();
	if (p == -1) {
		perror("fork");
		exit(errno);
	}
	if (p == 0) {
		printf("Exit code: %d", execvp(cmd[0], cmd));
	} else {
		;
	}
	return 1;
}
