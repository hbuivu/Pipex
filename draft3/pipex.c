#include "pipex.h"

// char	*here_doc(char *limiter)
// {
// 	char	*temp;
// 	char	*str;
// 	char	*new_str;
// 	int		lim_len;

// 	str = NULL;
// 	temp = NULL;
// 	new_str = NULL;
// 	lim_len = ft_strlen(limiter); 
// 	while (1)
// 	{
// 		temp = get_next_line(STDIN_FILENO);
// 		if (ft_strncmp(temp, limiter, lim_len) == 0)
// 			break;
// 		if (!str)
// 		{
// 			str = (char *)ft_calloc(ft_strlen(temp) + 1, sizeof(char));
// 			// if (!str)
// 			// 	//error
// 			ft_strlcpy(str, temp, ft_strlen(temp) + 1);
// 			free(temp);
// 		}
// 		else 
// 		{
// 			new_str = ft_strjoin(str, temp);
// 			free (str);
// 			free (temp);
// 			str = new_str; 
// 		}
// 	}
// 	free(temp);
// 	return (str);
// }

// void	here_doc(t_mlist *m)
// {
// 	int	fd[2];
// 	int	pid;
// 	int	lim_len;
// 	char	*line;

// 	if (pipe(fd) == -1)
// 		pipex_error(PIPE_ERR, m);
// 	pid = fork();
// 	if (pid == -1)
// 		pipex_error(FORK_ERR, m);
// 	else if (pid == 0)
// 	{
// 		lim_len = ft_strlen(m->limiter); 
// 		close(fd[0]);
// 		while (1)
// 		{
// 			line = get_next_line(STDIN_FILENO);
// 			if (ft_strncmp(line, m->limiter, lim_len) == 0)
// 			{
// 				free(line);
// 				close(fd[1]); //do i close this or keep it open?
// 				return ;
// 			}
// 			write(fd[1], line, ft_strlen(line));
// 			free(line);
// 		}
// 	}
// 	close(fd[1]);
// 	dup2(fd[0], STDIN_FILENO);
// 	waitpid(pid, NULL, 0);
// }

// void	send_here_doc(t_mlist *m)
// {
// 	int		fd[2];
// 	int		pid;
// 	char	*input;

// 	if (pipe(fd) == -1)
// 		pipex_error(PIPE_ERR, m);
// 	pid = fork();
// 	if (pid == -1)
// 		pipex_error(FORK_ERR, m);
// 	else if (pid == 0)
// 	{
// 		close(fd[0]);
// 		input = here_doc(m->limiter);
// 		write(fd[1], input, ft_strlen(input) + 1); //check get next line again because each line has a null ending
// 		close(fd[1]);
// 		return;
// 	}
// 	close(fd[1]);
// 	dup2(fd[0], STDIN_FILENO);
// 	close(fd[0]);
// 	return ;

// }

// int	here_doc(t_mlist *m)
// {
// 	int	fd[2];
// 	int	lim_len;
// 	char	*line;

// 	if (pipe(fd) == -1)
// 		pipex_error(PIPE_ERR, m);
// 	lim_len = ft_strlen(m->limiter); 
// 	while (1)
// 	{
// 		line = get_next_line(STDIN_FILENO);
// 		if (ft_strncmp(line, m->limiter, lim_len) == 0)
// 		{
// 			free(line);
// 			close(fd[1]); //do i close this or keep it open?
// 		}
// 		write(fd[1], line, ft_strlen(line));
// 		free(line);
// 	}
// 	return (fd[0]);
// }

//send str to an fd 

void	pipex(t_mlist *m, char **envp)
{
	int	fd[m->num_cmds - 1][2];
	int	pid[m->num_cmds];
	int	i;
	int	j;

	// (void)envp;
	// (void)hd;
	if (dup2(m->file1, STDIN_FILENO) == -1)
		pipex_error(DUP_ERR, m);
	if (close(m->file1) == -1)
		pipex_error(CLOSE_ERR, m);
	// print_file (STDIN_FILENO);
	//create all pipes
	i = 0;
	while (i < m->num_cmds - 1)
	{
		if (pipe(fd[i]) == -1)
			pipex_error(PIPE_ERR, m);
		i++;
	}
	//start forking
	i = 0;
	while (i < m->num_cmds)
	{
		//create fork
		pid[i] = fork();
		if (pid[i] == -1)
			pipex_error(FORK_ERR, m);
		//run child before creating another fork
		if (pid[i] == 0)
		{
			//if first command, send stdout to the write end of pipe
			if (i == 0)
			{
				printf("First child process\n");
				if (dup2(fd[i][1], STDOUT_FILENO) == -1)
				{
					printf("error in 1\n");
					pipex_error(DUP_ERR, m);
				}
			}
			//if not first command, read from prior pipe as stdin
			if (i > 0)
			{
				printf("Child process: %i, read from prior pipe\n", i);
				if(dup2(fd[i - 1][0], STDIN_FILENO) == -1)
				{
					printf("error in 2\n");
					pipex_error(DUP_ERR, m);
				}
			}
			//if last command, write to file2
			if (i == m->num_cmds - 1)
			{
				printf("last command, write to file2");
				if (dup2(m->file2, STDOUT_FILENO) == -1)
				{
					printf("error in 3\n");
					pipex_error(DUP_ERR, m);
				}
			}
			//if not the last command and not the first command, write stdout to next pipe
			else if (i > 0) //can this be combined? 
			{
				printf("child process: %i, write stdout to pipe\n", i);
				if (dup2(fd[i][1], STDOUT_FILENO) == -1)
				{
					printf("error in 4\n");
					pipex_error(DUP_ERR, m);
				}
			}
			j = 0;
			while (j < m->num_cmds - 1)
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
	while (j < m->num_cmds - 1)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
	i = 0;
	while (i < m->num_cmds)
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
	//for heredoc, argv has to be 6 
	if (ft_strncmp(argc[1], "here_doc", 9) == 0)
		hd = 1;
	else 
		if (access(argc[1], F_OK) < 0 || access(argc[1], R_OK) < 0)
			pipex_error(NO_FILE, m);
	m = init_mlist(argv, argc, envp, hd);
	print_mlist(m);
	pipex(m, envp);
	free_mlist(m);
	return (0);
}