/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:48:34 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/03/16 14:08:31 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_process_utils(int ***fd, int **pid, t_mlist *m)
{
	int	i;

	*fd = (int **)ft_calloc(m->num_cmds - 1, sizeof(int *));
	i = -1;
	while (++i < m->num_cmds)
		(*fd)[i] = (int *)ft_calloc(2, sizeof(int));
	*pid = (int *)ft_calloc(m->num_cmds, sizeof(int));
}

void	child_process(int i, int **fd, t_mlist *m, char **envp)
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

int	parent_process(int **fd, int *pid, t_mlist *m)
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
	free(pid);
	i = -1;
	while (++i < m->num_cmds)
		free(fd[i]);
	free(fd);
	return (status);
}

int	pipex(t_mlist *m, char **envp)
{
	int	**fd;
	int	*pid;
	int	i;
	int	status;

	create_process_utils(&fd, &pid, m);
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
	t_mlist	*m;
	int		hd;
	int		status;

	m = NULL;
	hd = 0;
	if (argc != 5)
		pipex_error(INVALID_ARG, m, NULL);
	m = init_mlist(argc, argv, envp, hd);
	status = pipex(m, envp);
	free_mlist(m);
	return (status);
}
