
void help(char *progname, char *errormsg);

enum Cipher_Type {
	CIPHER_CAESAR,
	CIPHER_MORSE,
	CIPHER_ROT13,
	CIPHER_COUNT,
	CIPHER_UNKNOWN,
};

struct cipher {
	enum Cipher_Type type;
};
