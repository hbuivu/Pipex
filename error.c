/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:43:34 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/03/17 12:07:15 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	return_err_message(int err)
{
	if (err == NO_ENV_PATH)
		ft_putstr_fd("PATH environmental variable unavailable", 2);
	else if (err == OPEN_ERR)
		perror("Open error");
	else if (err == MALLOC_ERR)
		perror("Malloc error");
	else if (err == PIPE_ERR)
		perror("Pipe error");
	else if (err == FORK_ERR)
		perror("Fork error");
	else if (err == DUP_ERR)
		perror("dup2 error");
	else if (err == CLOSE_ERR)
		perror("close error");
	else if (err == INVALID_ARG)
		ft_putstr_fd("usage: ./pipex file 1 cmd1 cmd2 file2\n", 2);
	else if (err == INVALID_BONUS_ARG)
		ft_putstr_fd("usage: ./pipex file 1 cmd1 cmd2 cmd 3... file2\n", 2);
	else if (err == INVALID_HEREDOC_ARG)
		ft_putstr_fd("usage: ./pipex heredoc LIMITER cmd1 cmd2 file\n", 2);
	return ;
}

void	free_splitlist(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}

void	free_execlist(t_mlist *m, t_exec *exec_list)
{
	int	i;

	i = 0;
	while (i < m->num_cmds)
	{
		if (exec_list[i].path)
			free(exec_list[i].path);
		if (exec_list[i].commands)
			free_splitlist(exec_list[i].commands);
		if (exec_list[i].type_commands)
			free_splitlist(exec_list[i].type_commands);
		i++;
	}
	free(exec_list);
}

void	free_mlist(t_mlist *m)
{
	int	i;

	if (m->exec_list)
		free_execlist(m, m->exec_list);
	if (m->env_paths)
		free_splitlist(m->env_paths);
	if (m->sh_path)
		free(m->sh_path);
	if (m->file1 >= 0)
		close(m->file1);
	if (m->file2 >= 0)
		close(m->file2);
	if (m->stderr_fd >= 0)
		close(m->stderr_fd);
	if (m->limiter)
		free(m->limiter);
	if (m->pid)
		free(m->pid);
	if (m->fd)
	{
		i = -1;
		while (++i < m->num_cmds - 1)
			free(m->fd[i]);
		free(m->fd);
	}
	free(m);
}

void	pipex_error(int err, t_mlist *m, char *str)
{
	if (err == NO_PATH)
		ft_printf_err("%s: command not found\n", str);
	else if (err == NO_FILE)
	{
		ft_printf_err("%s: No such file or directory\n", str);
		m->file1 = open("temp", O_CREAT | O_RDONLY | O_TRUNC, 0666); 
		if (!m->file1)
			pipex_error(OPEN_ERR, m, NULL);
	}
	else
	{
		return_err_message(err);
		if (m)
			free_mlist(m);
		// if (err == EXEC_ERR) // but what if there is an invalid file
		// 	exit(127);
		exit(1);
	}
}
