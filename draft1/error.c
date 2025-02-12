#include "pipex.h"

void	pipe_error(void)
{	
	perror("pipe error");
	exit(1);
}

void	fork_error(void)
{
	perror("fork error");
	exit(1);
}

void	access_error(void)
{
	perror("access not permitted to this command");
	exit(1);
}

void	exec_error(void)
{
	perror("exec error");
	exit(1);
}

void	path_error(void)
{
	perror("couldn't find PATH variable");
	exit(1);
}

void	arg_error(void)
{
	perror("input: ./pipex file1 cmd1 cmd2 file2");
	exit(1);
}
