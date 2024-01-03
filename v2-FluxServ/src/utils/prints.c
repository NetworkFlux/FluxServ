#include "v2-FluxServ.h"

static	void	putchar_fd(int fd, const char c)
{
	write(fd, &c, 1);
}

void	putstr_fd(int fd, const char* str)
{
	size_t	i;

	i = 0;
	while (str[i])
		putchar_fd(fd, str[i++]);
}