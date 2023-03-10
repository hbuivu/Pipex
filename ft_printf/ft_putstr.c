/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:46:59 by hbui-vu           #+#    #+#             */
/*   Updated: 2022/10/03 14:46:59 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str)
{
	int	count;

	count = 0;
	if (!str)
	{
		ft_putstr("(null)");
		count += 6;
	}
	else
	{
		while (*str)
		{
			ft_putchar(*(str++));
			count++;
		}
	}
	return (count);
}
