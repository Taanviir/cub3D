/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:56:26 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 13:27:33 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the last occurrence of character 'c' in the string 's'.
 *
 * @param s The input string to search.
 * @param c The character to be located.
 * @return A pointer to the matched character in 's', or NULL if 'c' is
 * not found.
 */
char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s) + 1;
	while (i--)
		if (s[i] == (char) c)
			return (i + (char *) s);
	return (NULL);
}
