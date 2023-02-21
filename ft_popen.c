//Steps:
//find which path 
//use dup to take from stdout
//use which to find path of inputted command
//use dup to take from stdout
//use path to execute first command


//ft_puststr_fd = output the string s to the given file descriptor

//find path to which command
//exec will overwrite and reclaim any memory that was malloc'd before

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
	path_list = ft_split(envp[i], ':');
	args = init_args();
	i = -1;
	while (path_list[++i])
	{
		path = ft_join(path_list[i], "/which");
		execve(path, args, envp);
		free(path);
	}
	free(path);
	free_split(path_list);
	exec_error();
}

// char	*ft_popen(const char *command)
// {
// 	int	fd[2];

// 	if (access(command, F_OK) < 0) //check to see if this is the correct mode
// 		access_error();
// 	if (pipe(fd) < 0)
// 		pipe_error();
// 	if (fork() < 0)
// 		fork_error();
// 	else if (fork == 0) //child
// 	{
// 		//find path to which command <- maybe this can be done in the main before
// 		//execute which on command
// 	}
// 	else //parent
// 	{
// 		//output from which command is put into string 
// 		//read output into a buffer
// 		//return buffer
// 		wait(NULL);
// 	}
// }

// #include <stdio.h>

// int main(void)
// {
// 	int i = -1;
// 	char *strs[] = {"a", "b", "c", "d", NULL};

// 	while (strs[++i])
// 		printf("%s\n", strs[i]);
// }