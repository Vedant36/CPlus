// I'm going to funcking(try to) implement every cipher on:
//         http://rumkin.com/tools/cipher/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "main.h"
#include "util.h"

int main(int argc, char **argv)
{
	if (argc < 2) {
		help(argv[0], "No arguments specified");
	} else {
		if (argv[1][0] != '-' && argv[1][2] != '\0') {
			fprintf(stderr, "Invalid argument!\n");
			return 1;
		}
		switch (argv[1][1]) {
		case 'h':
			help();
		default:
			;
		}
	}
	return 0;
}

void help(char *progname, char *errormsg)
{
	printf("Usage:\n");
	printf("    %s [-h|-l]\n", progname);
	printf("    %s -i CIPHERNAME\n", progname);
	printf("    %s [-e|-d] CIPHERNAME [FILE]...\n", progname);
	printf("\n");
	printf("With no FILE, or when FILE is -, read standard input.\n");
	printf("    -h   display this help message\n");
	printf("    -l   list all available ciphers\n");
	printf("    -i   display information on a cipher\n");
	printf("    -e   encrypt with a cipher\n");
	printf("    -d   decrypt(try to) with a cipher\n");
	printf("    -r   encrypt/decrypt raw text as argument\n");
	printf("    -o   provide an option to a cipher(like the rotation count for caesar cipher)\n");
	printf("    -a   has other cryptoanalysis tools\n");
	printf("\n");
	printf("Examples:\n");
	printf("    $ %s -i caesar\n", progname);
	printf("    $ cat /bin/cat | %s -e base64 > cat64\n", progname);
	printf("    $ %s -d rot13 file.txt\n", progname);
	printf("    $ %s -e rot13 file.txt\n", progname);
	if (errormsg != NULL) {
		printf("\n");
		printf("[Error] %s\n", errormsg);
		exit(1);
	}
	exit(0);
}
