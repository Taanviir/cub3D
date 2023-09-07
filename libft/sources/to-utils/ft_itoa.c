/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:50:04 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 13:07:17 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_length(long n)
{
	size_t	length;

	length = 0;
	if (n <= 0)
	{
		n *= -1;
		length++;
	}
	while (n > 0)
	{
		n /= 10;
		length++;
	}
	return (length);
}

/**
 * @brief Converts an integer 'n' to a string representation.
 *
 * @param n The integer to convert.
 * @return A pointer to the new string, or NULL if memory allocation fails.
 */
char	*ft_itoa(int n)
{
	char	*str;
	size_t	i;
	long	num;

	num = (long) n;
	i = int_length(num);
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (num == 0)
		str[0] = '0';
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	while (num > 0)
	{
		str[i] = (num % 10) + '0';
		num /= 10;
		i--;
	}
	return (str);
}
