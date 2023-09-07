/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:30:16 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 13:05:47 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isvalid(char c, char *base)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(base))
	{
		if (base[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	value_of(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

/**
 * @brief Converts the initial portion of the string 'str' to an integer
 * representation using a specified base.
 *
 * @param str The input string to convert.
 * @param base The base to be used for conversion (e.g., "0123456789abcdef").
 * @return The converted integer value.
 */
int	ft_atoi_base(const char *str, char *base)
{
	int	result;
	int	sign;

	result = 0;
	while (*str == ' ')
		str++;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (isvalid(*str, base))
		result = result * ft_strlen(base) + value_of(*str++);
	return (result * sign);
}
