/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:41:01 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/03/15 17:00:10 by hbui-vu          ###   ########.fr       */
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

int		check_command(char **commands, t_mlist *m, char **envp);
void	parse_builtin_comm(char *command, t_exec *exec_list, int i, t_mlist *m);
void	exec_command(char *command, t_mlist *m);
char	**get_env_paths(char **envp);
char	**get_type_commands(char *command, t_mlist *m);
int		detect_alnum(char *str);
void	free_splitlist(char **list);

void	print_file(int fd);
void	print_mlist(t_mlist *m);
void	print_splitlist(char **list);

#endif