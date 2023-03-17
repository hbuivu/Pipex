/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:48:34 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/03/17 11:39:22 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int i, t_mlist *m, char **envp)
{
	int	j;

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
	execve(m->exec_list[i].path, m->exec_list[i].commands, envp);
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
	if (close(m->file1) == -1)
		pipex_error(CLOSE_ERR, m, NULL);
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
	if (access("temp", F_OK) == 0)
		unlink("temp");
	return (status);
}
