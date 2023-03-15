#include "pipex.h"

void	exec_command(char *command, t_mlist *m)
{
	char *path;
	char **commands;
	char *str;
	char *args;

	path = get_path(m, "sh");
	str = ft_strjoin_char("type", command, ' ');
	args = ft_strjoin_char("sh,-c", str, ',');
	commands = ft_split(args, ',');
	free(str);
	free(args);
	if (execve(path, commands, NULL) == -1)
		pipex_error(EXEC_ERR, m, NULL);
}

int	check_command(char *command, t_mlist *m)
{
	int	fd[2];
	int	pid;
	char *buf;

	if (pipe(fd) == -1)
		pipex_error(PIPE_ERR, m, NULL);
	pid = fork();
	if (pid == -1)
		pipex_error(FORK_ERR, m, NULL);
	else if (pid == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			pipex_error(DUP_ERR, m, NULL);
		close(fd[0]);
		close(fd[1]);
		exec_command(command, m);
	}
	close(fd[1]);
	wait(NULL);
	buf = (char *)ft_calloc(1001, sizeof(char));
	read(fd[0], buf, 1000);
	printf("%s\n", buf);
	if (ft_strnstr(buf, "builtin", ft_strlen("builtin")) == NULL)
	{
		free(buf);
		return (0);
	}
	free(buf);
	close(fd[0]);
	return (1);
}

void	populate_builtin_comm(char *command, t_mlist *m, int i)
{
	char *args;

	args = ft_strjoin_char("sh,-c,", command, ',');
	if (!args)
		pipex_error(MALLOC_ERR, m, NULL);
	m->exec_list[i].path = get_path(m, "sh");
	if (!m->exec_list[i].path)
		pipex_error(NO_PATH, m, "sh");
	m->exec_list[i].commands = ft_split(args, ',');
	if (!m->exec_list[i].commands)
		pipex_error(MALLOC_ERR, m, NULL);
	free(args);
}

int main(void)
{
	int i = check_command("exit 5", NULL);
	printf("%i\n", i);
}
