#include "pipex.h"

void	child_process(int i, int (*fd)[2], t_mlist *m, char **envp)
{
	int	j;

	if (i == 0 && dup2(fd[i][1], STDOUT_FILENO) == -1)
		pipex_error(DUP_ERR, m, NULL);
	if (i > 0 && dup2(fd[i - 1][0], STDIN_FILENO) == -1)
		pipex_error(DUP_ERR, m, NULL);
	if (i == m->num_cmds - 1 && dup2(m->file2, STDOUT_FILENO) == -1)
		pipex_error(DUP_ERR, m, NULL);
	if (i != m->num_cmds - 1 && i > 0 && dup2(fd[i][1], STDOUT_FILENO) == -1)
		pipex_error(DUP_ERR, m, NULL);
	j = 0;
	while (j < m->num_cmds - 1)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
	execve(m->exec_list[i].path, m->exec_list[i].commands, envp);
	pipex_error(EXEC_ERR, m, NULL);
}

// void	parent_process(int (*fd)[2], int *pid, t_mlist *m)
// {
// 	int	i;

// 	i = 0;
// 	while (i < m->num_cmds - 1)
// 	{
// 		close(fd[i][0]);
// 		close(fd[i][1]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < m->num_cmds)
// 	{
// 		waitpid(pid[i], NULL, 0);
// 		i++;
// 	}
// }

// void	pipex(t_mlist *m, char **envp)
// {
// 	int	fd[m->num_cmds - 1][2];
// 	int	pid[m->num_cmds];
// 	int	i;

// 	if (dup2(m->file1, STDIN_FILENO) == -1)
// 		pipex_error(DUP_ERR, m, NULL);
// 	if (close(m->file1) == -1)
// 		pipex_error(CLOSE_ERR, m, NULL);
// 	i = -1;
// 	while (++i < m->num_cmds - 1)
// 		if (pipe(fd[i]) == -1)
// 			pipex_error(PIPE_ERR, m, NULL);
// 	i = -1;
// 	while (++i < m->num_cmds)
// 	{
// 		pid[i] = fork();
// 		if (pid[i] == -1)
// 			pipex_error(FORK_ERR, m, NULL);
// 		else if (pid[i] == 0)
// 			child_process(i, fd, m, envp);
// 	}
// 	parent_process(fd, pid, m);
// }

int	parent_process(int (*fd)[2], int *pid, t_mlist *m)
{
	int	i;
	int	status;

	i = 0;
	while (i < m->num_cmds - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	i = 0;
	while (i < m->num_cmds)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	return (status);
}

int	pipex(t_mlist *m, char **envp)
{
	int	fd[m->num_cmds - 1][2];
	int	pid[m->num_cmds];
	int	i;
	int	status;

	if (dup2(m->file1, STDIN_FILENO) == -1)
		pipex_error(DUP_ERR, m, NULL);
	if (close(m->file1) == -1)
		pipex_error(CLOSE_ERR, m, NULL);
	i = -1;
	while (++i < m->num_cmds - 1)
		if (pipe(fd[i]) == -1)
			pipex_error(PIPE_ERR, m, NULL);
	i = -1;
	while (++i < m->num_cmds)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			pipex_error(FORK_ERR, m, NULL);
		else if (pid[i] == 0)
			child_process(i, fd, m, envp);
	}
	status = parent_process(fd, pid, m);
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	t_mlist *m;
	int 	hd;
	int		status;

	m = NULL;
	hd = 0;
	if (argc != 5)
		pipex_error(INVALID_ARG, m, NULL);
	m = init_mlist(argc, argv, envp, hd);
	// print_mlist(m);
	status = pipex(m, envp);
	free_mlist(m);
	return(status);
}