#include "bonus_pipex.h"

char	*here_doc(t_mlist *m)
{
	char	*temp;
	char	*str;
	char	*new_str;
	int		lim_len;

	str = NULL;
	temp = NULL;
	new_str = NULL;
	lim_len = ft_strlen(m->limiter); 
	while (1)
	{
		temp = get_next_line(STDIN_FILENO);
		if (ft_strncmp(temp, m->limiter, lim_len) == 0)
			break;
		if (!str)
		{
			str = (char *)ft_calloc(ft_strlen(temp) + 1, sizeof(char));
			if (!str)
				pipex_error(MALLOC_ERR, m, NULL);
			ft_strlcpy(str, temp, ft_strlen(temp) + 1);
			free(temp);
		}
		else 
		{
			new_str = ft_strjoin(str, temp);
			free (str);
			free (temp);
			str = new_str; 
		}
	}
	free(temp);
	return (str);
}

int	here_doc_fd(t_mlist *m)
{
	int	fd[2];
	char *str;

	if (pipe(fd) == -1)
		pipex_error(PIPE_ERR, m, NULL);
	str = here_doc(m);
	write(fd[1], str, ft_strlen(str));
	close(fd[1]);
	return (fd[0]);
}