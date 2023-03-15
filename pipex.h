/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:41:01 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/03/13 13:42:07 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
	OPEN_ERR,
	MALLOC_ERR,
	PIPE_ERR,
	FORK_ERR,
	EXEC_ERR,
	DUP_ERR,
	CLOSE_ERR,
	INVALID_ARG,
	INVALID_HEREDOC_ARG
};

typedef struct execve_list
{
	char		*path;
	char		**commands;
}	t_exec;

typedef struct master_list
{
	t_exec	*exec_list;
	char	**env_paths;
	int		file1;
	int		file2;
	int		num_cmds;
	char	*limiter;
	int		lim_len;
}	t_mlist;

void	free_mlist(t_mlist *m);
void	pipex_error(int err, t_mlist *m, char *str);
t_mlist	*init_mlist(int argv, char **argc, char **envp, int hd);
int		here_doc_fd(t_mlist *m);
void	fill_heredoc_mlist(t_mlist *m, int argv, char **argc);
char	*ft_strjoin_char(char const *s1, char const *s2, char c);
char	*get_path(t_mlist *m, char *arg);

int	check_command(char *command, t_mlist *m);
void	populate_builtin_comm(char *command, t_mlist *m, int i);

void	print_file(int fd);
void	print_mlist(t_mlist *m);

#endif