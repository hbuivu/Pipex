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
	buffer = (char *)malloc(sizeof(char) * k);
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

	//if I put get envp_paths here, it will run the process each time I look for a path. So it might be easeir to put it in the mlist

	i = 0;
	while (m->env_paths[i])
	{
		path = ft_strjoin_char(m->env_paths[i], arg, '/');
		f = access(path, F_OK);
		x = access(path, X_OK);
		if (f == 0 && x == 0)
			break;
		else if (f == 0 && x < 0)
			pipex_error(NO_PATH, m);
		free(path);
		i++;
	}
	if (f == 0 && x == 0)
		return (path);
	return (NULL);
}

t_exec	*parse_paths(t_mlist *m, char **argc, int hd) //char **envp
{
	int		a;
	int		i;
	t_exec	*exec_list;

	exec_list = (t_exec *)ft_calloc(m->num_cmds, sizeof(t_exec));
	if (!exec_list)
		pipex_error(MALLOC_ERR, m);
	if (hd == 0)
		a = 2;
	else
		a = 3;
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
			break;
	if (envp[i] == NULL)
		return (NULL); 
	//move pointer over past =sign
	while (*(envp[i]) != '/')
		envp[i]++;
	env_paths = ft_split(envp[i], ':');
	if (!env_paths)
		return (NULL);
	return (env_paths);
}

// int	here_doc(t_mlist *m)
// {
// 	int	fd[2];
// 	int	lim_len;
// 	char	*line;

// 	if (pipe(fd) == -1)
// 		pipex_error(PIPE_ERR, m);
// 	lim_len = ft_strlen(m->limiter); 
// 	while (1)
// 	{
// 		line = get_next_line(STDIN_FILENO);
// 		if (ft_strncmp(line, m->limiter, lim_len) == 0)
// 		{
// 			free(line);
// 			close(fd[1]); //do i close this or keep it open?
// 		}
// 		write(fd[1], line, ft_strlen(line));
// 		free(line);
// 	}
// 	return (fd[0]);
// }
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
			// if (!str)
			// 	//error
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
		pipex_error(PIPE_ERR, m);
	// pipe(fd);
	str = here_doc(m);
	// printf("%s\n", str);
	write(fd[1], str, ft_strlen(str));
	close(fd[1]);
	return (fd[0]);
}
t_mlist	*init_mlist(int argv, char **argc, char **envp, int hd)
{
	t_mlist	*m;

	m = NULL;
	//malloc one mlist
	m = (t_mlist *)ft_calloc(1, sizeof(t_mlist));
	if (!m)
		pipex_error(MALLOC_ERR, m);
	//if heredoc, number of commands is argv - 4. Else it is argv - 3;
	if (hd == 0)
		m->num_cmds = argv - 3;
	else
		m->num_cmds = argv - 4;
	//create env paths to ref to each time find path
	m->env_paths = get_env_paths(envp); 
	if (!m->env_paths)
		pipex_error(NO_ENV_PATH, m);
	//Create exec_list - list of all env_paths and commands to be executed
	m->exec_list = parse_paths(m, argc, hd);
	//if not heredoc, open file1 and file2
	if (hd == 0)
	{
		m->file1 = open(argc[1], O_RDONLY);
		m->file2 = open(argc[argv - 1], O_CREAT | O_RDWR | O_TRUNC, 0666);
		if (m->file1 < 0 || m->file2 < 0)
			pipex_error(NO_FILE, m);
	}
	//if heredoc, open only file2 and create limiter
	else
	{
		m->limiter = ft_strjoin_char(argc[2], NULL, '\n');
		m->file1 = here_doc_fd(m);
		if (m->file1 < 0)
			pipex_error(NO_FILE, m);
		m->file2 = open(argc[argv - 1], O_CREAT | O_RDWR | O_APPEND, 0666);
		if (m->file2 < 0)
			pipex_error(NO_FILE, m);
		
	}
	return (m);
}
