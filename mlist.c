/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:17:35 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/03/15 17:17:57 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	detect_alnum(char *str)
{
	while (*str)
	{
		if (ft_isalnum(*str))
			return (1);
		str++;
	}
	return (0);
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
		f = access(path, F_OK);
		x = access(path, X_OK);
		if (f == 0 && x == 0)
			break ;
		else if (f == 0 && x < 0)
			return (NULL);
		free(path);
		i++;
	}
	if (f == 0 && x == 0)
		return (path);
	return (NULL);
}

t_exec	*parse_paths(t_mlist *m, char **argc, int hd, char **envp)
{
	int		a;
	int		i;
	t_exec	*exec_list;

	exec_list = (t_exec *)ft_calloc(m->num_cmds, sizeof(t_exec));
	if (!exec_list)
		pipex_error(MALLOC_ERR, m, NULL);
	if (hd == 0)
		a = 2;
	else
		a = 3;
	i = -1;
	while (++i < m->num_cmds)
	{
		//this technically does not need to be in the exec list but doing this to save space
		//also it cannot be used inside of check_command function bc it needs to be freed
		exec_list[i].type_commands = get_type_commands(argc[a], m);
		if (check_command(exec_list[i].type_commands, m, envp) == 1)
			parse_builtin_comm(argc[a], exec_list, i, m);
		else
		{
			exec_list[i].commands = ft_split(argc[a], ' ');
			if (!exec_list[i].commands)
				pipex_error(MALLOC_ERR, m, NULL);
			exec_list[i].path = get_path(m, exec_list[i].commands[0]);
			if (!exec_list[i].path)
				pipex_error(NO_PATH, m, exec_list[i].commands[0]);
		}
		a++;
	}
	return (exec_list);
}

t_mlist	*init_mlist(int argv, char **argc, char **envp, int hd)
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
		m->num_cmds = argv - 3;
		m->file1 = open(argc[1], O_RDONLY);
		if (m->file1 == -1)
			pipex_error(NO_FILE, m, argc[1]);
		m->file2 = open(argc[argv - 1], O_CREAT | O_RDWR | O_TRUNC, 0666);
		if (m->file2 == -1)
			pipex_error(OPEN_ERR, m, NULL);
	}
	else
		fill_heredoc_mlist(m, argv, argc);
	m->exec_list = parse_paths(m, argc, hd, envp);
	return (m);
}
