#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "pipex.h"
# include "./libft/libft.h"
# include "./ft_printf_err/ft_printf_err.h"
int main(int argv, char **argc, char **envp)
// int main(void)
{
	(void)argv;
	(void)argc;
	// char *path = "/usr/bin/sh";
	// char *args[5] = {"sh", "-c", "type -t type", NULL}; //why does this give an error?????
	// if (execve(path, args, envp) == -1)
	// 	printf("%s\n", strerror(errno));
	// char *str = NULL;
	// int	i = ft_printf_err("%s", str);
	// printf("%i\n", i);
	char *path = NULL;
	char *args[4] = {"something", "-c", "type urgh", NULL};
	execve(path, args, envp);
	printf("%s\n", strerror(errno));
	// printf("unsuccessful");

}

// https://stackoverflow.com/questions/66201463/how-can-i-print-the-exit-status-inside-of-the-code