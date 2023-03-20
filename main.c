/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:28:51 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/03/20 15:33:32 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_mlist	*m;
	int		hd;
	int		status;

	m = NULL;
	hd = 0;
	if (argc != 5)
		pipex_error(INVALID_ARG, m, NULL);
	m = init_mlist(argc, argv, envp, hd);
	status = pipex(m, envp);
	free_mlist(m);
	// if (access("temp", F_OK) == 0)
	// 	unlink("temp");
	return (status);
}