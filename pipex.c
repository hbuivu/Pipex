/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:48:34 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/03/20 17:37:24 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_nofile(t_mlist *m)
{
	int	devnull;
	int	j;

	devnull = open("/dev/null", O_WRONLY);
	dup2(devnull, STDOUT_FILENO);
	close(devnull);
	j = 0;
	while (j < m->num_cmds - 1)
	{
		close(m->fd[j][0]);
		close(m->fd[j][1]);
		j++;
	}
	exit(1);
}

void	child_process(int i, t_mlist *m, char **envp)
{
	int	j;
	
	if (i == 0 && m->nofile)
		process_nofile(m);
	if (i == 0 && dup2(m->fd[i][1], STDOUT_FILENO) == -1)
		pipex_error(DUP_ERR, m, NULL);
	if (i > 0 && dup2(m->fd[i - 1][0], STDIN_FILENO) == -1)
		pipex_error(DUP_ERR, m, NULL);
	if (i == m->num_cmds - 1 && dup2(m->file2, STDOUT_FILENO) == -1)
		pipex_error(DUP_ERR, m, NULL);
	if (i != m->num_cmds - 1 && i > 0 && dup2(m->fd[i][1], STDOUT_FILENO) == -1)
		pipex_error(DUP_ERR, m, NULL);
	j = 0;
	while (j < m->num_cmds - 1)
	{
		close(m->fd[j][0]);
		close(m->fd[j][1]);
		j++;
	}
	if (execve(m->exec_list[i].path, m->exec_list[i].commands, envp) == -1)
		pipex_error(EXEC_ERR, m, NULL);
}

int	parent_process(t_mlist *m)
{
	int	i;
	int	status;

	i = 0;
	while (i < m->num_cmds - 1)
	{
		close(m->fd[i][0]);
		close(m->fd[i][1]);
		i++;
	}
	i = 0;
	while (i < m->num_cmds)
	{
		waitpid(m->pid[i], &status, 0);
		i++;
	}
	return (status);
}

int	pipex(t_mlist *m, char **envp)
{
	int	i;
	int	status;
	
	if (dup2(m->file1, STDIN_FILENO) == -1)
		pipex_error(DUP_ERR, m, NULL);
	close(m->file1);
	m->file1 = -5;
	// if (close(m->file1) == -1)
	// 	pipex_error(CLOSE_ERR, m, NULL);
	i = -1;
	while (++i < m->num_cmds - 1)
		if (pipe(m->fd[i]) == -1)
			pipex_error(PIPE_ERR, m, NULL);
	i = -1;
	while (++i < m->num_cmds)
	{
		m->pid[i] = fork();
		if (m->pid[i] == -1)
			pipex_error(FORK_ERR, m, NULL);
		else if (m->pid[i] == 0)
			child_process(i, m, envp);
	}
	status = parent_process(m);
	return (WEXITSTATUS(status));
}
