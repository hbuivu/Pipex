/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:42:42 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/03/13 13:43:02 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin_char(char const *s1, char const *s2, char c)
{
	char	*buffer;
	int		k;
	int		i;

	if (!s1)
		return (NULL);
	if (!s2)
		k = ft_strlen(s1) + 2;
	else
		k = ft_strlen(s1) + ft_strlen(s2) + 2;
	buffer = (char *)ft_calloc(k, sizeof(char));
	if (!buffer)
		return (NULL);
	i = ft_strlcpy(buffer, s1, k);
	buffer[i] = c;
	if (s2)
		ft_strlcat(buffer, s2, k);
	return (buffer);
}

char	*get_path(t_mlist *m, char *arg)
{
	int		i;
	int		f;
	int		x;
	char	*path;

	i = 0;
	while (m->env_paths[i])
	{
		path = ft_strjoin_char(m->env_paths[i], arg, '/');
		f = access(path, F_OK);
		x = access(path, X_OK);
		if (f == 0 && x == 0)
			break ;
		else if (f == 0 && x < 0)
		{
			free(path);
			pipex_error(NO_PATH, m);
		}
		free(path);
		i++;
	}
	if (f == 0 && x == 0)
		return (path);
	return (NULL);
}

t_exec	*parse_paths(t_mlist *m, char **argc)
{
	int		a;
	int		i;
	t_exec	*exec_list;

	exec_list = (t_exec *)ft_calloc(m->num_cmds, sizeof(t_exec));
	if (!exec_list)
		pipex_error(MALLOC_ERR, m);
	a = 2;
	i = 0;
	while (i < m->num_cmds)
	{
		exec_list[i].commands = ft_split(argc[a], ' ');
		if (!exec_list[i].commands)
			pipex_error(MALLOC_ERR, m);
		exec_list[i].path = get_path(m, exec_list[i].commands[0]);
		if (!exec_list[i].path)
			pipex_error(NO_PATH, m);
		i++;
		a++;
	}
	return (exec_list);
}

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

t_mlist	*init_mlist(int argv, char **argc, char **envp)
{
	t_mlist	*m;

	m = NULL;
	m = (t_mlist *)ft_calloc(1, sizeof(t_mlist));
	if (!m)
		pipex_error(MALLOC_ERR, m);
	m->num_cmds = argv - 3;
	m->env_paths = get_env_paths(envp);
	if (!m->env_paths)
		pipex_error(NO_ENV_PATH, m);
	m->exec_list = parse_paths(m, argc);
	m->file1 = open(argc[1], O_RDONLY);
	m->file2 = open(argc[argv - 1], O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (m->file1 < 0 || m->file2 < 0)
		pipex_error(NO_FILE, m);
	return (m);
}
