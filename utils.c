/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:31:51 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/03/17 12:06:11 by hbui-vu          ###   ########.fr       */
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

void	init_fd_pid(t_mlist *m)
{
	int	i;

	m->fd = (int **)ft_calloc(m->num_cmds - 1, sizeof(int *));
	if (!m->fd)
		pipex_error(MALLOC_ERR, m, NULL);
	i = 0;
	while (i < m->num_cmds - 1)
	{
		m->fd[i] = (int *)ft_calloc(2, sizeof(int));
		if (!m->fd[i])
			pipex_error(MALLOC_ERR, m, NULL);
		i++;
	}
	m->pid = (int *)ft_calloc(m->num_cmds, sizeof(int));
	if (!m->pid)
		pipex_error(MALLOC_ERR, m, NULL);
	m->stderr_fd = open("stderr", O_CREAT | O_RDONLY | O_TRUNC, 0666);
	if (!m->stderr_fd)
		pipex_error(OPEN_ERR, m, NULL);
}
