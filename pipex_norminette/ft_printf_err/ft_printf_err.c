/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:46:37 by hbui-vu           #+#    #+#             */
/*   Updated: 2022/10/03 14:46:37 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_err.h"

int	is_format(char c)
{
	if (c == 'c' || c == 's')
		return (1);
	return (0);
}

int	write_format(va_list ptr, char c)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar((unsigned char)va_arg(ptr, int));
	else if (c == 's')
		count += ft_putstr(va_arg(ptr, char *));
	return (count);
}

int	ft_printf_err(const char *str, ...)
{
	int		i;
	int		count;
	va_list	ptr;

	i = 0;
	count = 0;
	va_start(ptr, str);
	while (str[i])
	{
		if (str[i] == '%' && is_format(str[i + 1]))
		{
			count += write_format(ptr, str[i + 1]);
			i++;
		}	
		else
			count += ft_putchar(str[i]);
		i++;
	}
	va_end(ptr);
	return (count);
}
