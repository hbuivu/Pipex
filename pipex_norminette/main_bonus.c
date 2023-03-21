/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:29:29 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/03/20 15:51:22 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_mlist	*m;
	int		hd;
	int		status;

	m = NULL;
	if (argc < 2)
		pipex_error(INVALID_ARG, m, NULL);
	hd = 0;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		hd = 1;
	if (hd == 0 && argc < 5)
		pipex_error(INVALID_BONUS_ARG, m, NULL);
	else if (hd == 1 && argc < 6)
		pipex_error(INVALID_HEREDOC_ARG, m, NULL);
	m = init_mlist(argc, argv, envp, hd);
	status = pipex(m, envp);
	free_mlist(m);
	return (status);
}
