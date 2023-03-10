/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexcap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:45:34 by hbui-vu           #+#    #+#             */
/*   Updated: 2022/10/04 08:54:08 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthexcap(unsigned int n)
{
	char	*base;
	int		count;

	base = "0123456789ABCDEF";
	count = 0;
	if (n < 16)
	{
		count += ft_putchar(base[n]);
	}
	else
	{
		count += ft_puthexcap(n / 16);
		count += ft_puthexcap(n % 16);
	}
	return (count);
}
