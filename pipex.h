#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "./libft/libft.h"

enum	e_perrors
{
	NO_ENV_PATH, //no PATH environmental variable
	NO_PATH,
	NO_FILE,
	MALLOC_ERR, 
	PIPE_ERR,
	FORK_ERR,
	EXEC_ERR,
	DUP_ERR,
	COMMAND_ERR,
	OPTION_ERR,
	INVALID_ARG
};

typedef struct	execve_list
{
	char		*path;
	char		**commands;
	// execve_list	*next;
}	t_exec;

typedef struct	master_list
{
	t_exec	*exec_list;
	char	**paths; //for main2
	int		file1;
	int		file2;
	int		num_commands;
}	t_mlist;


#endif