#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "./libft/libft.h"

void	pipe_error(void);
void	fork_error(void);
void	access_error(void);
void	exec_error(void);
void	path_error(void);


void	free_split(char **list);

#endif