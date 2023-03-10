/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:44:41 by hbui-vu           #+#    #+#             */
/*   Updated: 2022/10/04 08:54:02 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putmem(unsigned long long i)
{
	char	*base;
	int		count;

	base = "0123456789abcdef";
	count = 0;
	if (i < 16)
		count += ft_putchar(base[i]);
	else
	{
		count += ft_putmem(i / 16);
		count += ft_putmem(i % 16);
	}
	return (count);
}
