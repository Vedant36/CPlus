#define _POSIX_C_SOURCE 200809L
	#include <stdio.h>
	#include <stdlib.h>         /* standard library definitions */
	#include <unistd.h>         /* all system calls */
	#include <stdarg.h>         /* access to the va_* macros */
	#include <string.h>
	#include <ctype.h>
	#include <signal.h>
	#include <math.h>
	#include <limits.h>
	#include <errno.h>          /* errno reporting */
	#include <sys/types.h>      /* type pid_t */
	#include <time.h>           /* to profile code with nanosecond accuracy */
	#include <curses.h>

int main()
{
	__int128 a = 0;
	printf("%d", a);
	return 0;
}

