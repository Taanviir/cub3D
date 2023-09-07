/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:49:42 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 13:22:32 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_char(char const c, char const *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Removes leading and trailing characters from the string 's'
 * that are present in the string 'set'.
 *
 * @param s1 The input string to be trimmed.
 * @param set The set of characters to trim.
 * @return A pointer to the new trimmed string, or NULL if malloc fails.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*arr;
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s1)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && check_char(s1[start], set))
		start++;
	while (end > start && check_char(s1[end - 1], set))
		end--;
	arr = malloc(sizeof(*s1) * (end - start + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (start < end)
		arr[i++] = s1[start++];
	arr[i] = '\0';
	return (arr);
}
