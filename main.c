#include "pipex.h"

//error function
//free_split function

m_list	*init_mlist(int argv, char **argc)
{
	m_list	*m;

	m = (m_list *)ft_calloc(1, sizeof(m_list));
	if (!m)
		//error
	m->file1 = open(argc[1], O_RDONLY);
	m->file2 = open(argc[4], O_CREAT | O_WRONLY | O_TRUNC);
	if (m->file1 < 0 || m->file2 < 0)
		//free m
		//error
	m->num_commands = argv - 3;
	//in bonus, this will change with heredoc
	m->exec_list = (t_exec **)ft_calloc(1, sizeof(t_exec *));
	if (!m->exec_list)
		//free m 
		//close file1 and file2
		//error
	return (m);
}

char	*get_path(int fd)
{
	int		i;
	char	*path;

	path = get_next_line(fd);
	//if !path
		//exit
	i = -1;
	while(path[++i])
		if (path[i] == '\n')
			path[i] = '\0';
	return (path);
}

char	*find_which_path(char **envp)
{
	int		i;
	char	**path_list;
	char	**args; 
	char	*path;

	i = -1;
	while (envp[++i])
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			break;
	if (envp[i] == NULL)
		return (NULL);
	path_list = ft_split(envp[i], ':');
	args = ft_split("which which", ' ');
	i = -1;
	while (path_list[++i])
	{
		path = ft_strjoin(path_list[i], "/which");
		execve(path, args, envp);
		free(path);
	}
	free(path);
	free_split(path_list);
	exec_error();
}

char	*return_which_path(char **envp)
{
	int		fd[2];
	int		pid;
	char	*which_path;

	which_path = NULL;
	if (pipe(fd) < 0)
		pipe_error();
	pid = fork();
	if (pid < 0)
		fork_error();
	else if (pid == 0) //child
	{
		close(fd[0]);
		dup2(fd[1], 1);
		find_which_path(envp);
	}
	else //parent
	{
		wait(NULL);
		close(fd[1]);
		which_path = get_path(fd[0]);
		close(fd[0]);
	}
	return (which_path);
}

char	*find_path(char *which_path, char *command)
{
}

void	parse_paths(m_list *m, char **argc, char **envp)
{
	int		i;
	char	*which_path;
	t_exec	*node;
	t_exec	*curr;

	i = 2;
	*(m->exec_list) = NULL;
	curr = *(m->exec_list);
	which_path = find_which_path(envp);
	if (which_path == NULL)
		//do the other way
	while (i < m->num_commands)
	{
		//iterate through argc
		//create t_exec node
			//check path
			//check command
		//Current node = node;
		node = (t_exec *)ft_calloc(1, sizeof(t_exec));
		if (!node)
			//free m
			//exit
		node->commands = ft_split(argc, ' '); //check ft_split to see if everything gets freed during malloc error and returns NULL
		if (!node->commands)
			//free node;
			//free m and everything inside of m
			//error
		node->path = find_path(which_path, node->commands[0]);
		if (!node->path)
			//free node->commands
			//free node
			//free m and everything inside of m currently
			//error 
		node->next = NULL;
		if (!curr)
			curr = node;
		else
			curr->next = node;
	}
}

int	main(int argv, char **argc, char **envp)
{
	m_list	*m;

	if (argv != 5)
		return ;
	if (access(argc[1], F_OK) < 0 || access(argc[1], R_OK) < 0)
		return ; //return error?
	m = init_mlist(argv, argc);
	parse_paths(m, argc, envp);
	pipex(m, envp);
}