#include "pipex.h"

void	pipex(char *arg, char *which_path, char **envp, int file1)
{
	int		fd[2];
	int		pid;
	char	*path;
	char	**args;
	int		file2;

	if (pipe(fd) < 0)
		pipe_error();
	pid = fork();
	if (pid < 0)
		fork_error();
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(file1, 0);
		dup2(fd[1], 1);
		path = find_path(arg, envp, which_path);
		args = ft_split(arg, ' ');
		execve(path, args, envp);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		file2 = open("file2", O_CREAT | O_RDWR | O_TRUNC, 0666);
		dup2(file2, fd[0]);
		// dup2(file2, 1);
		// char buf[2000];
		// read(fd[0], buf, 2000);
		// printf("%s", buf);
	}

}

int main(int argv, char **argc, char **envp)
{
	(void)argv;
	(void)argc;

	char *which_path;
	int	file1;
	// char *path;
	
	which_path = return_which_path(envp);
	file1 = open(argc[1], O_RDONLY);
	// printf("%s\n", which_path);
	pipex(argc[2], which_path, envp, file1);
	// path = find_path(argc[1], envp, which_path);
	// printf("%s\n", path);

}