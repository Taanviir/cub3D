/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:55:14 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 13:16:20 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies 'len' bytes from string 'src' to string 'dst'.
 * The two strings may overlap.
 *
 * @param dst Pointer to the destination string.
 * @param src Pointer to the source string.
 * @param len Maximum number of bytes to copy.
 * @return A pointer to the destination string ('dst').
 */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*source;
	char	*destination;

	if (!src && !dst)
		return (NULL);
	i = 0;
	source = (char *) src;
	destination = (char *) dst;
	if (src < dst)
		while (len--)
			destination[len] = source[len];
	else
	{
		while (len--)
		{
			destination[i] = source[i];
			i++;
		}
	}
	return (dst);
}
