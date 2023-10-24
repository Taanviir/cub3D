/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 02:53:41 by sabdelra          #+#    #+#             */
/*   Updated: 2022/12/08 17:42:59 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	new_line(char *stash)
{
	int	i;

	i = 0;
	while (stash && stash[i])
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	int	i;

	if (!dest && !src)
		return (NULL);
	if (dest < src)
	{
		i = 0;
		while (i < (int)size)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
	}
	else
	{
		i = (int)size - 1;
		while (i >= 0)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i--;
		}
	}
	return (dest);
}

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	dest_len;
	size_t	i;

	dest_len = ft_strlen(dest);
	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}
