#include "pipex.h"

void	pipex(char *arg) //use a struct?
{
	int		fd[2];
	int		pid;
	char	*path;
	char	**args;

	if(pipe(fd) < 0)
		pipe_error();
	pid = fork();
	if (pid < 0)
		fork_error();
	else if (pid == 0) //child process
	{
		close(fd[0]);
		dup2(file1, 0); //file1 is taken as the input
		dup2(fd[1], 1); //output will be written to fd[1] so it can be read by pipe
		path = find_path(arg, envp, which_path);
		args = ft_split(arg, ' ');
		execve(path, args, envp);
	}
	else //parent process
	{
		wait(NULL);
		close(fd[1]);
		dupe2(fd[0], 0); //output from child is taken as input
		dupe2(file2, 1); //final output is written to file2
		path = find_path(arg2, envp, which_path);
		args = ft_split(arg2, ' ');
		execve(path, args, envp;)
	}
}



