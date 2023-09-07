/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:47:23 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 13:21:25 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Extracts a substring from the string 's', starting at index 'start'
 * and extending to at most 'len' characters.
 *
 * @param s The input string to extract from.
 * @param start The start index of the substring.
 * @param len The maximum number of characters in the substring.
 * @return A pointer to the new substring, or NULL if memory allocation fails.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(s) <= len && ft_strlen(s) >= start)
		str = malloc((ft_strlen(s) - start) + 1);
	else
		str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
			str[j++] = s[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}
