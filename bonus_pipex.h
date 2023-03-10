#ifndef BONUS_PIPEX_H
# define BONUS_PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"

enum	e_perrors
{
	NO_ENV_PATH,
	NO_PATH,
	NO_FILE,
	INVALID_FILE,
	MALLOC_ERR, 
	PIPE_ERR,
	FORK_ERR,
	EXEC_ERR,
	DUP_ERR,
	COMMAND_ERR,
	OPTION_ERR,
	CLOSE_ERR,
	INVALID_ARG,
	INVALID_HEREDOC_ARG
};

typedef struct	execve_list
{
	char		*path;
	char		**commands;
}	t_exec;

typedef struct	master_list
{
	t_exec	*exec_list;
	int		no_path;
	char	**env_paths;
	int		file1;
	int		file2;
	int		num_cmds;
	char	*limiter;
}	t_mlist;

void	free_mlist(t_mlist *m);
void	pipex_error(int err, t_mlist *m, char *str);
t_mlist	*init_mlist(int argv, char **argc, char **envp, int hd);
int		here_doc_fd(t_mlist *m);


void	print_splitlist(char **list);
void		print_execlist(t_exec *e, int limit);
void	print_mlist(t_mlist *m);
void	print_file(int fd);


#endif