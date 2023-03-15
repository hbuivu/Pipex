#include "pipex.h"

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

void	print_execlist(t_exec *e, int limit)
{
	int	i;

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
	printf("NUM_COMMANDS: %i\n", m->num_cmds);
	printf("PATHS: ");
	print_splitlist(m->env_paths);
	printf("SHELL PATH: %s\n", m->sh_path);
	printf("EXEC LIST\n");
	print_execlist(m->exec_list, m->num_cmds);
	printf("LIMITER: %s\n", m->limiter);
}

void	print_file(int fd)
{
	char *buf;

	buf = (char *)ft_calloc(2500, sizeof(char));
	read(fd, buf, 2499);
	printf("%s\n", buf);
}