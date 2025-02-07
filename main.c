/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:28:51 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/03/21 13:23:06 by hbui-vu          ###   ########.fr       */
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
	print_splitlist(envp);
	if (argc != 5)
		pipex_error(INVALID_ARG, m, NULL);
	m = init_mlist(argc, argv, envp, hd);
	status = pipex(m, envp);
	free_mlist(m);
	return (status);
}
