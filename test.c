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
	int fd[2];
	int	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		// char *path = "/bin/sh";
		// char *args[4] = {"sh", "-c", "type urgh", NULL};
		char *path = "/bin/ls";
		char *args[4] = {"ls", "ls", NULL};
		close(fd[0]);
		dup2(fd[1], STDERR_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		
		close(fd[1]);
		if (execve(path, args, envp) == -1)
			exit(1);
	}
	wait(NULL);
	char buf[2000];
	close(fd[1]);
	read(fd[0], buf, 1000);
	// printf("%s\n", buf);
	close(fd[0]);
	return (0);
	// char *path = "/usr/bin/sh";
	// char *args[5] = {"sh", "-c", "type -t type", NULL}; //why does this give an error?????
	// if (execve(path, args, envp) == -1)
	// 	printf("%s\n", strerror(errno));
	// char *str = NULL;
	// int	i = ft_printf_err("%s", str);
	// printf("%i\n", i);

	// printf("%s\n", strerror(errno));
	// printf("unsuccessful");

}


// https://stackoverflow.com/questions/66201463/how-can-i-print-the-exit-status-inside-of-the-code