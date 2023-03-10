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

#include "ft_printf.h"

int	is_format(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X' || c == '%')
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
	else if (c == 'p')
	{
		count += ft_putstr("0x");
		count += ft_putmem((unsigned long long)va_arg(ptr, void *));
	}
	else if (c == 'd' || c == 'i')
		count += ft_putnbr(va_arg(ptr, int));
	else if (c == 'u')
		count += ft_putunbr(va_arg(ptr, unsigned int));
	else if (c == 'x')
		count += ft_puthex(va_arg(ptr, int));
	else if (c == 'X')
		count += ft_puthexcap(va_arg(ptr, int));
	else if (c == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *str, ...)
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
