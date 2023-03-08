void	pipex(t_mlist *m, char **envp) //this one only has one pipe
{
	int	fd[m->num_commands - 1][2];
	int	pid[m->num_commands];
	int	i;
	int	j;

	if (dup2(m->file1, STDIN_FILENO) < 0)
		pipex_error(DUP_ERR, m);
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
			if (i == 0 && dup2(fd[i][1], STDOUT_FILENO) < 0)
				pipex_error(DUP_ERR, m);
			//if not first command, read from prior pipe as stdin
			if (i > 0 && dup2(fd[i][0], STDIN_FILENO) < 0)
				pipex_error(DUP_ERR, m);
			//if last command, write to file2
			if (i == m->num_commands - 1 && dup2(m->file2, STDOUT_FILENO) < 0)
				pipex_error(DUP_ERR, m);
			//if not the last command and not the first command, write stdout to next pipe
			else if (i > 0 && dup2(fd[i + 1][1], STDOUT_FILENO) < 0)
				pipex_error(DUP_ERR, m);
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
		close(fd[i][0]);
		close(fd[i][1]);
		j++;
	}
	i = 0;
	while (i < m->num_commands)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}