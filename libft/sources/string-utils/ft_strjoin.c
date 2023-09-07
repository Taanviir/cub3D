/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:47:35 by tanas             #+#    #+#             */
/*   Updated: 2023/08/01 10:12:53 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Joins two strings 'stash' and 'buffer' into a new string.
 * The resulting string is a combination of both strings.
 *
 * @param stash The first part of the resulting string.
 * @param buffer The second part of the resulting string.
 * @return A pointer to the new concatenated string, or NULL
 * if memory allocation fails.
 */
char	*ft_strjoin(char *stash, char *buffer)
{
	char	*string;
	int		i;
	int		j;

	if (!buffer)
		return (NULL);
	string = malloc(ft_strlen(stash) + ft_strlen(buffer) + 1);
	if (!string)
		return (NULL);
	i = 0;
	while (stash && stash[i])
	{
		string[i] = stash[i];
		i++;
	}
	j = 0;
	while (buffer[j])
		string[i++] = buffer[j++];
	string[i] = '\0';
	return (string);
}

/***
 * @brief Joins two strings 'stash' and 'buffer' into a new string.
 * 
 * @param stash The first part of the resulting string.
 * @param buffer The second part of the resulting string.
 * @return A pointer to the new concatenated string, or NULL
*/
char	*ft_strjoin_m(char *stash, char *buffer)
{
	char	*string;
	int		i;
	int		j;

	if (!buffer)
		return (NULL);
	string = malloc(ft_strlen(stash) + ft_strlen(buffer) + 1);
	if (!string)
		return (NULL);
	i = 0;
	while (stash && stash[i])
	{
		string[i] = stash[i];
		i++;
	}
	free(stash);
	j = 0;
	while (buffer[j])
		string[i++] = buffer[j++];
	string[i] = '\0';
	return (string);
}

/***
 * @brief Gets a variable number of strings and joins them into one.
 * 
 * @param count The number of strings to join.
 * @param ... The strings to join.
 * @return A pointer to the new concatenated string, or NULL
*/
char	*ft_bigjoin(int count, ...)
{
	va_list	args;
	char	*result;
	int		i;

	va_start(args, count);
	result = NULL;
	i = -1;
	while (++i < count)
		result = ft_strjoin_m(result, va_arg(args, char *));
	va_end(args);
	return (result);
}
