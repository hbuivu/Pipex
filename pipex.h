#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "./libft/libft.h"

// typedef struct exec_list
// {
// 	char	*which_path;
// 	char	*path;
// }	t_exec;

void	pipe_error(void);
void	fork_error(void);
void	access_error(void);
void	exec_error(void);
void	path_error(void);


void	free_split(char **list);

char	*find_path(char *command, char **envp, char *which_path);
char	*return_which_path(char **envp);

void	print_args(char **list);
#endif