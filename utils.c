/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:31:51 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/03/16 13:55:23 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	detect_alnum(char *str)
{
	while (*str)
	{
		if (ft_isalnum(*str))
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strjoin_char(char const *s1, char const *s2, char c)
{
	char	*buffer;
	int		k;
	int		i;

	if (!s1)
		return (NULL);
	if (!s2)
		k = ft_strlen(s1) + 2;
	else
		k = ft_strlen(s1) + ft_strlen(s2) + 2;
	buffer = (char *)ft_calloc(k, sizeof(char));
	if (!buffer)
		return (NULL);
	i = ft_strlcpy(buffer, s1, k);
	buffer[i] = c;
	if (s2)
		ft_strlcat(buffer, s2, k);
	return (buffer);
}
