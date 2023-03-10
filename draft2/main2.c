#include "pipex.h"
#include "utils.c"

char	**get_PATHS(char **envp)
{
	int		i;
	char	**paths;

	i = -1;
	while (envp[++i])
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			break;
	if (envp[i] == NULL)
		return (NULL); 
	//move pointer over past =sign
	while (*(envp[i]) != '/')
		envp[i]++;
	paths = ft_split(envp[i], ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*ft_strjoin_char(char const *s1, char const *s2, char c)
{
	char	*buffer;
	int		k;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	k = ft_strlen(s1) + ft_strlen(s2) + 2;
	buffer = (char *)malloc(sizeof(char) * k);
	if (!buffer)
		return (NULL);
	i = ft_strlcpy(buffer, s1, k);
	buffer[i] = c;
	ft_strlcat(buffer, s2, k);
	return (buffer);
}

char	*find_path(t_mlist *m, char *arg) //char **envp
{
	int		i;
	int		f;
	int		x;
	char	*path;

	i = 0;
	while (m->paths[i])
	{
		path = ft_strjoin_char(m->paths[i], arg, '/');
		f = access(path, F_OK);
		x = access(path, X_OK);
		if (f == 0 && x == 0)
			break;
		else if (f == 0 && x < 0)
			pipex_error(NO_PATH, m);
		free(path);
		i++;
	}
	if (f == 0 && x == 0)
		return (path);
	return (NULL);
}

void	parse_paths(t_mlist *m, char **argc, int hd) //char **envp
{
	int		a;
	int		i;
	t_exec	*exec;

	if (hd == 0)
		a = 2;
	else
		a = 3;
	i = 0;
	exec = m->exec_list;
	while (i < m->num_commands)
	{
		exec[i].commands = ft_split(argc[a], ' ');
		if (!exec[i].commands)
			pipex_error(MALLOC_ERR, m);
		exec[i].path = find_path(m, exec[i].commands[0]);
		if (!exec[i].path)
			pipex_error(NO_PATH, m);
		i++;
		a++;
	}
}


// void	simple_pipex(t_mlist *m, char **envp) //this one only has one pipe
// {
// 	int	fd[2];
// 	if (dup2(m->file1, STDIN_FILENO) < 0)
// 		pipex_error(DUP_ERR, m);
// 	if (pipe(fd) < 0)
// 		pipex_error(PIPE_ERR, m);
// 	int	pid1 = fork();
// 	if (pid1 < 0)
// 		pipex_error(FORK_ERR, m);
// 	if (pid1 == 0) //child process
// 	{
// 		dup2(fd[1], STDOUT_FILENO); //send output to fd[1];
// 		close(fd[0]);
// 		close(fd[1]);
// 		execve(m->exec_list[0].path, m->exec_list[0].commands, envp);
// 	}
// 	int pid2 = fork();
// 	if (pid2 < 0)
// 		pipex_error(FORK_ERR, m);
// 	if (pid2 == 0)
// 	{
// 		//the output from pid1 was sent to fd[0]. send that to stdin
// 		if (dup2(fd[0], STDIN_FILENO) < 0) 
// 			pipex_error(DUP_ERR, m); 
// 		//send the output to file2
// 		if (dup2(m->file2, STDOUT_FILENO) < 0)
// 			pipex_error(DUP_ERR, m);
// 		close(fd[0]);
// 		close(fd[1]);
// 		execve(m->exec_list[1].path, m->exec_list[1].commands, envp);
// 	}

// 	close(fd[0]);
// 	close(fd[1]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// }

// void	simple_pipex_three(t_mlist *m, char **envp) //this one only has one pipe
// {
// 	int	fd[2][2];
// 	int	i;

// 	if (dup2(m->file1, STDIN_FILENO) < 0)
// 		pipex_error(DUP_ERR, m);
// 	i = 0;
// 	while (i < 2)
// 	{
// 		if (pipe(fd[i]) < 0)
// 			pipex_error(PIPE_ERR, m);
// 		i++;
// 	}
// 	int	pid1 = fork();
// 	if (pid1 < 0)
// 		pipex_error(FORK_ERR, m);
// 	if (pid1 == 0) //child process
// 	{
// 		if (dup2(fd[0][1], STDOUT_FILENO) < 0) //send output to fd[1];
// 			pipex_error(DUP_ERR, m);
// 		i = 0;
// 		while (i < 2)
// 		{
// 			close(fd[i][0]);
// 			close(fd[i][1]);
// 			i++;
// 		}
// 		execve(m->exec_list[0].path, m->exec_list[0].commands, envp);
// 	}
// 	int pid2 = fork();
// 	if (pid2 < 0)
// 		pipex_error(FORK_ERR, m);
// 	if (pid2 == 0)
// 	{
// 		if (dup2(fd[0][0], STDIN_FILENO) < 0)
// 			pipex_error(DUP_ERR, m);
// 		if (dup2(fd[1][1], STDOUT_FILENO) < 0)
// 			pipex_error(DUP_ERR, m);
// 		i = 0;
// 		while (i < 2)
// 		{
// 			close(fd[i][0]);
// 			close(fd[i][1]);
// 			i++;
// 		}
// 		execve(m->exec_list[1].path, m->exec_list[1].commands, envp);
// 	}
// 	int pid3 = fork();
// 	if (pid3 < 0)
// 		pipex_error(FORK_ERR, m);
// 	if (pid3 == 0)
// 	{
// 		//the output from pid1 was sent to fd[0]. send that to stdin
// 		if (dup2(fd[1][0], STDIN_FILENO) < 0) 
// 			pipex_error(DUP_ERR, m); 
// 		//send the output to file2
// 		if (dup2(m->file2, STDOUT_FILENO) < 0)
// 			pipex_error(DUP_ERR, m);
// 		i = 0;
// 		while (i < 2)
// 		{
// 			close(fd[i][0]);
// 			close(fd[i][1]);
// 			i++;
// 		}
// 		execve(m->exec_list[2].path, m->exec_list[2].commands, envp);
// 	}
// 	i = 0;
// 	while (i < 2)
// 	{
// 		close(fd[i][0]);
// 		close(fd[i][1]);
// 		i++;
// 	}
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// 	waitpid(pid3, NULL, 0);
// }

void	pipex(t_mlist *m, char **envp)
{
	int	fd[m->num_commands - 1][2];
	int	pid[m->num_commands];
	int	i;
	int	j;

	if (dup2(m->file1, STDIN_FILENO) < 0)
		pipex_error(DUP_ERR, m);
	close(m->file1);
	i = 0;
	while (i < m->num_commands - 1)
	{
		if (pipe(fd[i]) < 0)
			pipex_error(PIPE_ERR, m);
		i++;
	}
	i = 0;
	while (i < m->num_commands)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			pipex_error(FORK_ERR, m);
		if (pid[i] == 0)
		{
			//if first command, send stdout to the write end of pipe
			if (i == 0)
			{
				printf("First child process\n");
				if (dup2(fd[i][1], STDOUT_FILENO) < 0)
				{
					printf("error in 1\n");
					pipex_error(DUP_ERR, m);
				}
			}
			//if not first command, read from prior pipe as stdin
			if (i > 0)
			{
				printf("Child process: %i, read from prior pipe\n", i);
				if(dup2(fd[i - 1][0], STDIN_FILENO) < 0)
				{
					printf("error in 2\n");
					pipex_error(DUP_ERR, m);
				}
			}
			//if last command, write to file2
			if (i == m->num_commands - 1)
			{
				printf("last command, write to file2");
				if (dup2(m->file2, STDOUT_FILENO) < 0)
				{
					printf("error in 3\n");
					pipex_error(DUP_ERR, m);
				}
			}
			//if not the last command and not the first command, write stdout to next pipe
			else if (i > 0)
			{
				printf("child process: %i, write stdout to pipe\n", i);
				if (dup2(fd[i][1], STDOUT_FILENO) < 0)
				{
					printf("error in 4\n");
					pipex_error(DUP_ERR, m);
				}
			}
			j = 0;
			while (j < m->num_commands - 1)
			{
				close(fd[j][0]);
				close(fd[j][1]);
				j++;
			}
			execve(m->exec_list[i].path, m->exec_list[i].commands, envp);
			pipex_error(EXEC_ERR, m);
		}
		i++;
	}
	j = 0;
	while (j < m->num_commands - 1)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
	i = 0;
	while (i < m->num_commands)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}

int	main(int argv, char **argc, char **envp)
{
	t_mlist	*m;
	int		hd; 

	m = NULL;
	hd = 0;
	// if (argv != 5)
	// 	pipex_error(INVALID_ARG, m);
	if (argv < 5)
		pipex_error(INVALID_ARG, m);
	if (ft_strncmp(argc[1], "here_doc", 9) == 0)
		hd = 1;
	else 
		if (access(argc[1], F_OK) < 0 || access(argc[1], R_OK) < 0)
			pipex_error(NO_FILE, m);
	m = init_mlist(argv, argc, envp, hd);
	// print_mlist(m);
	pipex(m, envp);
	free_mlist(m);
	return (0);
}
