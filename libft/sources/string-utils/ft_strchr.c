/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:56:05 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 13:24:09 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the first occurrence of character 'c'
 * in the string 's'.
 *
 * @param s The input string to search.
 * @param c The character to be located.
 * @return A pointer to the matched character in 's', or NULL if 'c'
 * is not found.
 */
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char) c)
			return (i + (char *) s);
		i++;
	}
	if (s[i] == (char) c)
		return (i + (char *) s);
	return (NULL);
}
