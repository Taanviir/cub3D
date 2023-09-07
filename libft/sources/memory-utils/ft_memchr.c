/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:53:48 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 13:17:50 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the first occurrence of 'c' (converted to an unsigned char)
 * in the initial 'n' bytes of the memory area pointed by 's'.
 *
 * @param s Pointer to the memory area to be searched.
 * @param c The character to be located.
 * @param n Number of bytes to be searched.
 * @return A pointer to the matching byte, or NULL if no character is found.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*string;

	i = 0;
	string = (const char *) s;
	while (i < n)
	{
		if (string[i] == (char) c)
			return ((void *)(string + i));
		i++;
	}
	return (NULL);
}
