/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:17:35 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/03/20 16:38:05 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_env_paths(char **envp)
{
	int		i;
	char	**env_paths;

	i = -1;
	while (envp[++i])
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			break ;
	if (envp[i] == NULL)
		return (NULL);
	while (*(envp[i]) != '/')
		envp[i]++;
	env_paths = ft_split(envp[i], ':');
	if (!env_paths)
		return (NULL);
	return (env_paths);
}

char	*get_path(t_mlist *m, char *arg)
{
	int		i;
	char	*path;

	i = 0;
	if (!arg || !detect_alnum(arg))
		return (NULL);
	if (access(arg, F_OK) == 0 && access(arg, X_OK) == 0)
	{
		path = ft_strdup(arg);
		if (!path)
			pipex_error(MALLOC_ERR, m, NULL);
		return (path);
	}
	while (m->env_paths[i])
	{
		path = ft_strjoin_char(m->env_paths[i], arg, '/');
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
			return (path);
		else if (access(path, F_OK) == 0 && access(path, X_OK) < 0)
			return (NULL);
		free(path);
		i++;
	}
	return (NULL);
}

void	set_counters(int hd, int *a, int *i)
{
	if (hd == 0)
		*a = 2;
	else
		*a = 3;
	*i = -1;
}

void	parse_paths(t_mlist *m, char **argv, int hd, char **envp)
{
	int		a;
	int		i;

	m->exec_list = (t_exec *)ft_calloc(m->num_cmds, sizeof(t_exec));
	if (!m->exec_list)
		pipex_error(MALLOC_ERR, m, NULL);
	set_counters(hd, &a, &i);
	while (++i < m->num_cmds)
	{
		m->exec_list[i].type_commands = get_type_commands(argv[a], m);
		if (check_command(m->exec_list[i].type_commands, m, envp) == 1)
			parse_builtin_comm(argv[a], i, m);
		else
		{
			m->exec_list[i].commands = ft_split(argv[a], ' ');
			if (!m->exec_list[i].commands)
				pipex_error(MALLOC_ERR, m, NULL);
			m->exec_list[i].path = get_path(m, m->exec_list[i].commands[0]);
			if (!m->exec_list[i].path)
				pipex_error(NO_PATH, m, m->exec_list[i].commands[0]);
		}
		a++;
	}
}

t_mlist	*init_mlist(int argc, char **argv, char **envp, int hd)
{
	t_mlist	*m;

	m = NULL;
	m = (t_mlist *)ft_calloc(1, sizeof(t_mlist));
	if (!m)
		pipex_error(MALLOC_ERR, m, NULL);
	m->env_paths = get_env_paths(envp);
	if (!m->env_paths)
		pipex_error(NO_ENV_PATH, m, NULL);
	m->sh_path = get_path(m, "sh");
	if (hd == 0)
	{
		m->num_cmds = argc - 3;
		m->file1 = open(argv[1], O_RDONLY);
		if (m->file1 == -1)
			pipex_error(NO_FILE, m, argv[1]);
		m->file2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0666);
		if (m->file2 == -1)
			pipex_error(OPEN_ERR, m, NULL);
	}
	else
		fill_heredoc_mlist(m, argc, argv);
	parse_paths(m, argv, hd, envp);
	init_fd_pid(m);
	return (m);
}
