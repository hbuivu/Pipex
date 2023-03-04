#include "pipex.h"

// void	output_to_file(char *arg, int fd) //do you have to fork?
// {
// 	int	pid;

// 	pid = fork();
// 	if (pid < 0)
// 		fork_error();
// 	else if (pid == 0)
// 	{
// 		if (dup2(fd, STDOUT_FILENO) < 0)
// 			dup2_error(); //must make this later
// 		close(fd);
// 		//execute command
// 		//exec_error();
// 	}
// 	else
// 	{
// 		if (wait(NULL) < 0) //only need to use waitpid if waiting for a partiular child
// 			wait_error(); //must make this later
// 		close(fd);
// 	}
// 	//dup2(fd, STDOUT_FILENO);
// 	//close(fd);
// 	//execve(commmand)
// }

// void	pipex()
// {
// 	int	fd[2];
// 	int	pid;

// 	if (pipe(fd) < 0)
// 		pipe_error();
// 	pid = fork();
// 	if (pid < 0)
// 		fork_error();
// 	else if (pid == 0)
// 	{
// 		close(fd[0]);
// 		dup2(file1, STDIN_FILENO);
// 		dup2(fd[1], STDOUT_FILENO);
// 	}
// 	else
// 	{
// 		if (wait(NULL) < 0)
// 			wait_error();
// 		output_to_file();

		
// 	}
// }
// void	pipex(char *arg, char *which_path, char **envp, int file1)
// {
// 	int		fd[2];
// 	int		pid;
// 	char	*path;
// 	char	**args;
// 	int		file2;

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
// 		path = find_path(arg, envp, which_path);
// 		args = ft_split(arg, ' ');
// 		close(fd[1]);
// 		execve(path, args, envp);
// 	}
// 	else
// 	{
// 		wait(NULL);
// 		close(fd[1]);
// 		file2 = open("file2", O_CREAT | O_RDWR | O_TRUNC, 0666); 
// 		// dup2(file2, fd[0]);
// 		// close(file2);
// 		// char buf[2000];
// 		// read(fd[0], buf, 2000);
// 		// printf("%s\n", buf);
// 		// write_to_file(fd[0]);
// 		dup2(file2, STDOUT_FILENO);
// 	}

// }

int main(int argv, char **argc, char **envp)
{
	(void)argv;
	(void)argc;
	(void)envp;

	// char *which_path;
	// int	file1;
	// // char *path;
	
	// which_path = return_which_path(envp);
	// file1 = open(argc[1], O_RDONLY);
	// // printf("%s\n", which_path);
	// pipex(argc[2], which_path, envp, file1);
	// // path = find_path(argc[1], envp, which_path);
	// // printf("%s\n", path);

	int i = access("which", F_OK);
	printf("%i\n", i);
}