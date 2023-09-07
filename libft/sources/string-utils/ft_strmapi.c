/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:49:30 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 13:24:42 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Applies the function 'f' to each character of the string 's'
 * to create a new string resulting from successive applications of 'f'.
 *
 * @param s The input string to iterate through.
 * @param f The function to apply to each character.
 * @return A pointer to the new string, or NULL if memory allocation fails.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*arr;
	size_t	i;

	if (!s)
		return (NULL);
	arr = malloc(ft_strlen(s) + 1);
	if (!arr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		arr[i] = f(i, s[i]);
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
