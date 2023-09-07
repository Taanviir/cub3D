/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:56:01 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 13:15:54 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Fills the first 'len' bytes of the memory area pointed by 'b'
 * with the constant byte 'c'.
 *
 * @param b Pointer to the memory area to be filled.
 * @param c The value to be set ('c' is converted to an unsigned char).
 * @param len Number of bytes to be set.
 * @return A pointer to the memory area 'b'.
 */
void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *) b;
	while (len--)
	{
		p[i] = (unsigned char) c;
		i++;
	}
	return (b);
}
