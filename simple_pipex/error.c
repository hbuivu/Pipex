#include "pipex.h"

void	return_err_message(int err)
{
	if (err == NO_ENV_PATH)
		ft_putstr_fd("PATH environmental variable unavailable", 2);
	else if (err == NO_PATH)
		perror("Path not found");
	else if (err == NO_FILE)
		perror("Unable to open file");
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
		perror("invalid option"); //check later - option error is when the option for the command is invalid
	else if (err == CLOSE_ERR)
		perror("close error"); 
	else if (err == INVALID_ARG) //also need the err for heredoc
		ft_putstr_fd("usage: ./pipex file 1 com1 com2 file2\n", 2);
}

void	free_splitlist(char **list)
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

void	free_execlist(t_mlist *m, t_exec *exec_list)
{
	int	i;

	i = 0;
	while (i < m->num_cmds)
	{
		free(exec_list[i].path);
		if (exec_list[i].commands)
			free_splitlist(exec_list[i].commands);
		i++;
	}
	free(exec_list);
}

void	free_mlist(t_mlist *m)
{
	if (m->exec_list)
		free_execlist(m, m->exec_list);
	if (m->env_paths)
		free_splitlist(m->env_paths);
	if (m->file1 >= 0)
		close(m->file1);
	if (m->file2 >= 0)
		close(m->file2);
	if (m->limiter)
		free(m->limiter);
	free(m);
}

void	pipex_error(int err, t_mlist *m)
{
	return_err_message(err);
	if (m)
		free_mlist(m);
	exit(1);
}