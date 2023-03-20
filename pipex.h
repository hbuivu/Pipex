/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:41:01 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/03/20 16:41:45 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "./libft/libft.h"
# include "./ft_printf_err/ft_printf_err.h"

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
	INVALID_BONUS_ARG,
	INVALID_HEREDOC_ARG
};

typedef struct execve_list
{
	char	*path;
	char	**commands;
	char	**type_commands;
}	t_exec;

typedef struct master_list
{
	t_exec	*exec_list;
	char	**env_paths;
	char	*sh_path;
	int		**fd;
	int		*pid;
	int		file1;
	int		file2;
	int		nofile;
	int		num_cmds;
	char	*limiter;
	int		lim_len;
}	t_mlist;

/* error.c */
void	free_mlist(t_mlist *m);
void	free_splitlist(char **list);
void	pipex_error(int err, t_mlist *m, char *str);

/* utils.c */
char	*ft_strjoin_char(char const *s1, char const *s2, char c);
int		detect_alnum(char *str);
void	init_fd_pid(t_mlist *m);

/* mlist.c */
t_mlist	*init_mlist(int argc, char **argv, char **envp, int hd);

/* heredoc.c */
void	fill_heredoc_mlist(t_mlist *m, int argv, char **argc);

/* builtin_commands.c */
int		check_command(char **commands, t_mlist *m, char **envp);
char	**get_type_commands(char *command, t_mlist *m);
void	parse_builtin_comm(char *command, int i, t_mlist *m);

 /* pipex.c */
 int	pipex(t_mlist *m, char **envp);

/* testing.c */
void	print_file(int fd);
void	print_mlist(t_mlist *m);
void	print_splitlist(char **list);

#endif