/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:11:38 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/03/20 15:50:07 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*init_str(char *temp, t_mlist *m)
{
	char	*str;

	str = (char *)ft_calloc(ft_strlen(temp) + 1, sizeof(char));
	if (!str)
		pipex_error(MALLOC_ERR, m, NULL);
	ft_strlcpy(str, temp, ft_strlen(temp) + 1);
	free(temp);
	return (str);
}

char	*here_doc(t_mlist *m)
{
	char	*temp;
	char	*str;
	char	*new_str;

	str = NULL;
	temp = NULL;
	new_str = NULL;
	while (1)
	{
		temp = get_next_line(STDIN_FILENO);
		if (ft_strncmp(temp, m->limiter, m->lim_len) == 0)
			break ;
		if (!str)
			str = init_str(temp, m);
		else
		{
			new_str = ft_strjoin(str, temp);
			free(str);
			free(temp);
			str = new_str;
		}
	}
	free(temp);
	return (str);
}

int	heredoc_fd(t_mlist *m)
{
	int		fd[2];
	char	*str;

	if (pipe(fd) == -1)
		pipex_error(PIPE_ERR, m, NULL);
	str = here_doc(m);
	write(fd[1], str, ft_strlen(str));
	free(str);
	close(fd[1]);
	return (fd[0]);
}

void	fill_heredoc_mlist(t_mlist *m, int argc, char **argv)
{
	m->num_cmds = argc - 4;
	m->limiter = ft_strjoin_char(argv[2], NULL, '\n');
	if (!m->limiter)
		pipex_error(MALLOC_ERR, m, NULL);
	m->lim_len = ft_strlen(m->limiter);
	m->file1 = heredoc_fd(m);
	m->file2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 0666);
	if (m->file1 == -1 || m->file2 == -1)
		pipex_error(OPEN_ERR, m, NULL);
}
