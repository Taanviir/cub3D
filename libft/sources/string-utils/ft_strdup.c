/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:56:10 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 13:27:47 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Duplicates a string 's1' and returns a pointer to the new
 * duplicated string.
 *
 * @param s1 The input string to be duplicated.
 * @return A pointer to the new duplicated string, or NULL if memory
 * allocation fails.
 */
char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	i;

	dup = malloc(ft_strlen(s1) + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
