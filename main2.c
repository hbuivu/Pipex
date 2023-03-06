#include "pipex.h"
#include "utils.c"

char	**get_PATHS(char **envp)
{
	int		i;
	char	**paths;

	i = -1;
	while (envp[++i])
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			break;
	if (envp[i] == NULL)
		return (NULL); 
	//move pointer over past =sign
	while (*(envp[i]) != '/')
		envp[i]++;
	paths = ft_split(envp[i], ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*ft_strjoin_char(char const *s1, char const *s2, char c)
{
	char	*buffer;
	int		k;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	k = ft_strlen(s1) + ft_strlen(s2) + 2;
	buffer = (char *)malloc(sizeof(char) * k);
	if (!buffer)
		return (NULL);
	i = ft_strlcpy(buffer, s1, k);
	buffer[i] = c;
	ft_strlcat(buffer, s2, k);
	return (buffer);
}

char	*find_path(t_mlist *m, char *arg) //char **envp
{
	int		i;
	int		f;
	int		x;
	char	*path;

	i = 0;
	while (m->paths[i])
	{
		path = ft_strjoin_char(m->paths[i], arg, '/');
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

void	parse_paths(t_mlist *m, char **argc) //char **envp
{
	int		a;
	int		i;
	t_exec	*exec;

	a = 2;
	i = 0;
	exec = m->exec_list;
	while (i < m->num_commands)
	{
		exec[i].commands = ft_split(argc[a], ' ');
		if (!exec[i].commands)
			pipex_error(MALLOC_ERR, m);
		exec[i].path = find_path(m, exec[i].commands[0]);
		if (!exec[i].path)
			pipex_error(NO_PATH, m);
		i++;
		a++;
	}
}

t_mlist	*init_mlist(int argv, char **argc, char **envp)
{
	t_mlist	*m;

	m = NULL;
	m = (t_mlist *)ft_calloc(1, sizeof(t_mlist));
	if (!m)
		pipex_error(MALLOC_ERR, m);
	m->num_commands = argv - 3;
	//in bonus, this will change with heredoc
	m->paths = get_PATHS(envp);
	if (!m->paths)
		pipex_error(NO_ENV_PATH, m);
	m->exec_list = (t_exec *)ft_calloc(m->num_commands, sizeof(t_exec));
	if (!m->exec_list)
		pipex_error(MALLOC_ERR, m);
	parse_paths(m, argc);
	m->file1 = open(argc[1], O_RDONLY);
	m->file2 = open(argc[argv - 1], O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (m->file1 < 0 || m->file2 < 0)
		pipex_error(NO_FILE, m);
	return (m);
}

// void	pipex(t_mlist *m, char **envp)
// {
// 	int	i;
// 	int	pid;
// 	int	fd[2];

// 	if (dup2(m->file1, STDIN_FILENO) < 0)
// 		pipex_error(DUP_ERR, m);
// 	close(m->file1);
// 	i = 0;
// 	while (i < m->num_commands)
// 	{
// 		if (pipe(fd) < 0)
// 			pipex_error(PIPE_ERR, m);
// 		pid = fork();
// 		if (pid < 0)
// 			pipex_error(FORK_ERR, m);
// 		else if (pid == 0)
// 		{
// 			printf("child process: %i\n", i);
// 			close(fd[0]);
// 			printf("PRINTING INPUT FILE: \n");
// 			print_file(STDIN_FILENO);
// 			if (i == m->num_commands - 1)
// 			{
// 				if (dup2(m->file2, STDOUT_FILENO) < 0)
// 					pipex_error(DUP_ERR, m);
// 			}
// 			else if (i < m->num_commands - 1)
// 			{
// 				if (dup2(fd[1], STDOUT_FILENO) < 0)
// 					pipex_error(DUP_ERR, m);
// 			}
// 			close(fd[1]);
// 			close(m->file1);
// 			close(m->file2);
// 			execve(m->exec_list[i].path, m->exec_list[i].commands, envp);
// 			pipex_error(EXEC_ERR, m);
// 		}
// 		else
// 		{
// 			wait(NULL);
// 			close(fd[1]);
// 			if (i != m->num_commands - 1)
// 			{
// 				if (dup2(fd[0], STDIN_FILENO) < 0)
// 					pipex_error(DUP_ERR, m);
// 			}
// 			close(fd[0]);
// 			printf("parent process: %i\n", i);
// 			printf("PRINTING STDIN: \n");
// 			print_file(STDIN_FILENO);
// 			i++;
// 		}
// 	}
// }

void	pipex(t_mlist *m, char **envp)
{
	int	i;
	int	pid;
	int	fd[2];

	if (dup2(m->file1, STDIN_FILENO) < 0)
		pipex_error(DUP_ERR, m);
	close(m->file1);
	i = 0;
	while (i < m->num_commands)
	{
		if (pipe(fd) < 0)
			pipex_error(PIPE_ERR, m);
		pid = fork();
		if (pid < 0)
			pipex_error(FORK_ERR, m);
		else if (pid == 0)
		{
			close(fd[0]);
			if (i == m->num_commands - 1)
			{
				if (dup2(m->file2, STDOUT_FILENO) < 0)
					pipex_error(DUP_ERR, m);
			}
			else if (i < m->num_commands - 1)
			{
				if (dup2(fd[1], STDOUT_FILENO) < 0)
					pipex_error(DUP_ERR, m);
			}
			close(fd[1]);
			close(m->file1);
			close(m->file2);
			execve(m->exec_list[i].path, m->exec_list[i].commands, envp);
			pipex_error(EXEC_ERR, m);
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			printf("printing file\n");
			print_file(fd[0]);
			// if (i != m->num_commands - 1)
			// {
			// 	if (dup2(fd[0], STDIN_FILENO) < 0)
			// 		pipex_error(DUP_ERR, m);
			// }
			close(fd[0]);
			i++;
		}
	}
}

int	main(int argv, char **argc, char **envp)
{
	t_mlist	*m;

	m = NULL;
	// if (argv != 5)
	// 	pipex_error(INVALID_ARG, m);
	if (access(argc[1], F_OK) < 0 || access(argc[1], R_OK) < 0)
		pipex_error(NO_FILE, m);
	m = init_mlist(argv, argc, envp);
	print_mlist(m);
	// int i = 0;
	// if (dup2(m->file1, STDIN_FILENO) < 0)
	// 	pipex_error(DUP_ERR, m);
	// execve(m->exec_list[i].path, m->exec_list[i].commands, envp);
	// pipex(m, envp);
	// free_mlist(m);
	return (0);
}