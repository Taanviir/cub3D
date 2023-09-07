/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:56:15 by tanas             #+#    #+#             */
/*   Updated: 2023/08/01 10:13:02 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Calculates the length of the string 's', excluding the 
 * terminating null byte.
 *
 * @param s The input string.
 * @return The length of the string.
 */
size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (s && s[size])
		size++;
	return (size);
}
