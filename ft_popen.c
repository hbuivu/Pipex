#include "pipex.h"
//Steps:
//find which path 
//use dup to take from stdout
//use which to find path of inputted command
//use dup to take from stdout
//use path to execute first command

//ft_puststr_fd = output the string s to the given file descriptor
//find path to which command

//case:
//what if which doesn't work?
//what if which can't find the path?
	
void	find_which_path(char **envp)
{
	int		i;
	char	**path_list;
	char	**args; 
	char	*path;

	i = -1;
	while (envp[++i])
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			break;
	//what happens if PATH= cannot be found????
	if (envp[i] == NULL)
		path_error();
	path_list = ft_split(envp[i], ':');
	args = ft_split("which which", ' ');
	i = -1;
	while (path_list[++i])
	{
		path = ft_strjoin(path_list[i], "/which");
		execve(path, args, envp);
		free(path);
	}
	free(path);
	free_split(path_list);
	exec_error();
}

char	*return_which_path(char **envp)
{
	int		fd[2];
	int		pid;
	char	*which_path;

	// if (access(command, F_OK) < 0) //check to see if this is the correct mode
	// 	access_error();
	which_path = NULL;
	if (pipe(fd) < 0)
		pipe_error();
	pid = fork();
	if (pid < 0)
		fork_error();
	else if (pid == 0) //child
	{
		close(fd[0]);
		dup2(fd[1], 1);
		find_which_path(envp);
	}
	else //parent
	{
		wait(NULL);
		close(fd[1]);
		which_path = ft_calloc(1024, sizeof(char)); //instead of calloc 1024, count length of path
		read(fd[0], which_path, 1024);
		close(fd[0]);
		// printf("now in parent directory\n");
		// printf("%s", which_path);
	}
	return (which_path);
}

//run which + command -> return path
char	*ft_popen(char *command, char **envp, char *which_path)
{
	char	**args;
	int		fd[2];
	int		pid;
	char	*path;

	printf("entering ft_popen\n");
	path = NULL;
	if(pipe(fd) < 0) //free which_path
		pipe_error();
	pid = fork();
	if (pid < 0) //free which_path
		fork_error();
	else if (pid == 0) //child process
	{
		printf("entering child process\n");
		close(fd[0]);
		args = ft_split(command, ' '); //check ft_split to see if it frees stuff if malloc error
		dup2(fd[1], 1);
		execve(which_path, args, envp);
	}
	else //parent process
	{
		wait(NULL);
		close(fd[1]);
		path = ft_calloc(1024, sizeof(char));
		read(fd[1], path, 1024);
		close(fd[0]);
	}
	return (path);
}

#include <stdio.h>

int main(int argv, char **argc, char **envp)
{
	(void)argv;
	(void)argc;
	char *which_path;
	// char *path;

	which_path = return_which_path(envp);
	printf("%s", which_path);
	// char *command = "which ls";
	//char **commands = ft_split(command, ' ');
	// path = ft_popen("which ls", envp, which_path);
	// printf("%s", which_path);
	// printf("%s", path);
	// for (int i = 0; i < 3; i++)
	// 	printf("%s\n", commands[i]);
	// execve(which_path, commands, envp);
	char *args[] = {
		"which",
		"ls",
		NULL
	};
	execve(which_path, args, envp);
}