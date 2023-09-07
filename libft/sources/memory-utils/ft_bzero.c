/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:53:29 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 13:09:35 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Fills the first 'n' bytes of the memory area with zeroes.
 *
 * @param s Pointer to the memory area to be zeroed.
 * @param n Number of bytes to zero.
 */
void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (n--)
	{
		((unsigned char *) s)[i] = 0;
		i++;
	}
}
