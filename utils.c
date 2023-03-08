#include "pipex.h"

void	return_err_message(int err)
{
	if (err == NO_ENV_PATH)
		ft_putstr_fd("PATH environmental variable unavailable", 2);
	else if (err == NO_PATH)
		perror("Path not found: ");
	else if (err == NO_FILE)
		perror("Unable to open file: ");
	else if (err == MALLOC_ERR)
		perror("Malloc error: ");
	else if (err == PIPE_ERR)
		perror("Pipe error: ");
	else if (err == FORK_ERR)
		perror("Fork error: ");
	else if (err == EXEC_ERR)
		perror("exec error: ");
	else if (err == DUP_ERR)
		perror("dup2 error");
	else if (err == COMMAND_ERR)
		perror("Command not found"); //check later
	else if (err == OPTION_ERR)
		perror("invalid option"); //check later
	else if (err == INVALID_ARG)
		ft_putstr_fd("usage: ./pipex file 1 com1 com2 file2\n", 2);
}

void	free_split(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}

// void	free_texec(t_exec **exec_list)
// {
// 	t_exec *cur;
// 	t_exec	*temp;

// 	cur = *exec_list;
// 	while (cur)
// 	{
// 		free(cur->path);
// 		free_split(cur->commands);
// 		temp = cur;
// 		cur = cur->next;
// 		free(temp);
// 	}
// 	free(exec_list)
// }

void	free_texec(t_mlist *m, t_exec *exec_list)
{
	int	i;

	i = 0;
	while (i < m->num_commands)
	{
		free(exec_list[i].path);
		if (exec_list[i].commands)
			free_split(exec_list[i].commands);
		// free(exec_list[i]); //do I have to free this?
		i++;
	}
	free(exec_list);
}

void	free_mlist(t_mlist *m)
{
	if (m->exec_list)
		free_texec(m, m->exec_list);
	if (m->paths)
		free_split(m->paths);
	if (m->file1 >= 0)
		close(m->file1);
	if (m->file2 >= 0)
		close(m->file2);
	free(m);
}

void	pipex_error(int err, t_mlist *m)
{
	return_err_message(err);
	if (m)
		free_mlist(m);
	exit(1);
}

// z: command not found
// ls: invalid option -- 'z'

void	print_splitlist(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		printf("%s, ", list[i]);
		i++;
	}
	printf("\n");
}

void		print_execlist(t_exec *e, int limit)
{
	int i;

	i = 0;
	while (i < limit && e)
	{
		printf("PATH: %s\n", e[i].path);
		printf("COMMANDS: ");
		print_splitlist(e[i].commands);
		i++;
	}
}

void	print_mlist(t_mlist *m)
{
	printf("FD: file1: %i file2: %i\n", m->file1, m->file2);
	printf("NUM_COMMANDS: %i\n", m->num_commands);
	printf("PATHS: ");
	print_splitlist(m->paths);
	printf("EXEC LIST\n");
	print_execlist(m->exec_list, m->num_commands);
	
}

void	print_file(int fd)
{
	char *buf;

	buf = (char *)ft_calloc(2500, sizeof(char));
	read(fd, buf, 2499);
	printf("%s\n", buf);
}