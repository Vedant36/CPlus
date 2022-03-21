#include <string.h>

enum Cipher_Type cipher_lookup(char *ciphername)
{
	if (strcmp(ciphername, "caesar") == 0)
		return CIPHER_CAESAR;
	else if (strcmp(ciphername, "morse") == 0)
		return CIPHER_MORSE;
	else if (strcmp(ciphername, "rot13") == 0)
		return CIPHER_ROT13;
	else
		return CIPHER_UNKNOWN;
}
