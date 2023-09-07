/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:53:38 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 13:20:52 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates memory for an array of 'count' elements, each of
 * 'size' bytes, and initializes it with zeroes.
 *
 * @param count Number of elements in the array.
 * @param size Size of each element in bytes.
 * @return A pointer to the allocated memory, or NULL if allocation fails.
 */
void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;

	if (!count || !size || ((SIZE_MAX / count) < size))
		return (NULL);
	arr = malloc(count * size);
	if (!arr)
		return (NULL);
	ft_memset(arr, 0, size * count);
	return (arr);
}
