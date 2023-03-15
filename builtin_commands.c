/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:18:31 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/03/15 11:18:31 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	find_type(char *command, t_exec *exec_list, t_mlist *m, int i, char **envp)
// {
// 	char **primary_com;
// 	char *type_str;
// 	char *type_args;
// 	(void)envp;
// 	(void)i;

// 	primary_com = ft_split(command, ' ');
// 	print_splitlist(primary_com);
// 	if (!primary_com)
// 		pipex_error(MALLOC_ERR, m, NULL);
// 	type_str = ft_strjoin_char("type", primary_com[0], ' '); 
// 	printf("type str: %s\n", type_str);
// 	type_args = ft_strjoin_char("sh,-c", type_str, ',');
// 	printf("type_args: %s\n", type_args);
// 	if (!type_str || !type_args)
// 		pipex_error(MALLOC_ERR, m, NULL);
// 	exec_list[i].type_commands = ft_split(type_args, ',');
// 	// // print_splitlist(m->exec_list[i].type_commands);
// 	// if (!m->exec_list[i].type_commands)
// 	// 	pipex_error(MALLOC_ERR, m, NULL);
// 	free(type_str);
// 	free(type_args);
// 	free(primary_com);
// 	// printf("sh path: %s\n", m->sh_path);
// 	// print_splitlist(m->exec_list[i].type_commands);
// 	// execve(m->sh_path, m->exec_list[i].type_commands, envp);
// 	// pipex_error(EXEC_ERR, m, NULL);
// }

char	**get_type_commands(char *command, t_mlist *m)
{
	char	**primary_com;
	char	*type_str;
	char	*type_args;
	char	**ret_args;

	if (!command || !detect_alnum(command))
		return (NULL);
	primary_com = ft_split(command, ' ');
	if (!primary_com)
		pipex_error(MALLOC_ERR, m, NULL);
	type_str = ft_strjoin_char("type", primary_com[0], ' '); 
	type_args = ft_strjoin_char("sh,-c", type_str, ',');
	if (!type_str || !type_args)
		pipex_error(MALLOC_ERR, m, NULL);
	ret_args = ft_split(type_args, ',');
	if (!ret_args)
		pipex_error(MALLOC_ERR, m, NULL);
	free(type_str);
	free(type_args);
	free_splitlist(primary_com);
	return(ret_args);
}

// int	check_builtin(int *fd, t_mlist *m)
// {
// 	char *buf;

// 	close(fd[1]);
// 	buf = (char *)ft_calloc(1001, sizeof(char));
// 	if (!buf)
// 		pipex_error(MALLOC_ERR, m, NULL);
// 	read(fd[0], buf, 1000);
// 	close(fd[0]);
// 	printf("buf: %s\n", buf);
// 	if (ft_strnstr(buf, "builtin", ft_strlen(buf) + 1) == NULL)
// 	{
// 		free(buf);
// 		return (0);
// 	}
// 	free(buf);
// 	return (1);
// }

int	check_command(char **commands, t_mlist *m, char **envp)
{
	int	fd[2];
	int	pid;

	if (!commands)
		return (0);
	if (pipe(fd) == -1)
		pipex_error(PIPE_ERR, m, NULL);
	pid = fork();
	if (pid == -1)
		pipex_error(FORK_ERR, m, NULL);
	else if (pid == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			pipex_error(DUP_ERR, m, NULL);
		close(fd[0]);
		close(fd[1]);
		execve(m->sh_path, commands, envp);
	}
	close(fd[1]);
	wait(NULL);
	char *buf = (char *)ft_calloc(1001, sizeof(char));
	if (!buf)
		pipex_error(MALLOC_ERR, m, NULL);
	read(fd[0], buf, 1000);
	close(fd[0]);
	if (ft_strnstr(buf, "builtin", ft_strlen(buf) + 1) == NULL)
	{
		free(buf);
		return (0);
	}
	free(buf);
	return (1);
}

void	parse_builtin_comm(char *command, t_exec *exec_list, int i, t_mlist *m)
{
	char *args;

	args = ft_strjoin_char("sh,-c,", command, ',');
	if (!args)
		pipex_error(MALLOC_ERR, m, NULL);
	exec_list[i].path = ft_strdup(m->sh_path);
	if (!exec_list[i].path)
		pipex_error(MALLOC_ERR, m, NULL);
	exec_list[i].commands = ft_split(args, ',');
	if (!exec_list[i].commands)
		pipex_error(MALLOC_ERR, m, NULL);
	free(args);
}
