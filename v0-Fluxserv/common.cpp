#include "common.hpp"

void	errNdie(const char *msg, ...)
{
	int		errSave;
	va_list	ap;

	// Any system or library call can set errno, so save it
	errSave = errno;

	// Print the message to std OUT
	va_start(ap, msg);
	vfprintf(stdout, msg, ap);	// vfprintf = variadic fprintf
	fprintf(stdout, "\n");
	fflush(stdout);				// Flush std OUT

	// If errno was set, print the error message
	if (errSave != 0)
	{
		fprintf(stdout, "(errno = %d) : %s\n", errSave, strerror(errSave));
		fprintf(stdout, "\n");
		fflush(stdout);
	}
	va_end(ap);

	exit(EXIT_FAILURE);
}

char*	bin2hex(const unsigned char* input, size_t len)
{
	char*	res;
	char*	hexits = "0123456789abcdef";
	int		resultLen;

	if (input == NULL || len <= 0)
		return NULL;

	resultLen = (len * 3) + 1;

	res = (char*)malloc(resultLen);
	bzero(res, resultLen);

	for (int i = 0; i < len; i++)
	{
		res[i * 3] = hexits[input[i] >> 4];
		res[(i * 3) + 1] = hexits[input[i] & 0x0F];
		res[(i * 3) + 2] = ' ';		// For readability
	}

	return (res);
}