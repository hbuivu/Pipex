#include "pipex.h"

// void	pipex()
// {
// 	int		fd[2];
// 	int		pid;
// 	char	*path;

// 	if (pipe(fd) < 0)
// 		pipe_error();
// 	pid = fork();
// 	if (pid < 0)
// 		fork_error();
// 	else if (pid == 0)
// 	{
// 		close(fd[0]);
// 		dup2(file1, 0);
// 		dup2(fd[1], 1);
// 		path = find_path();
// 	}
// 	else
// 	{
// 		wait(NULL);
// 	}
// }

int main(int argv, char **argc, char **envp)
{
	(void)argv;
	(void)argc;

	char *which_path;
	
	which_path = return_which_path(envp);
	// printf("%s\n", which_path);
	pipex()
}