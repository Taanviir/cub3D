/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 09:23:32 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 13:05:30 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Converts the initial portion of the string 'str' to an integer.
 *
 * @param str The input string to convert.
 * @return The converted integer value.
 */
int	ft_atoi(const char *str)
{
	int	sign;
	int	pos;
	int	num;

	pos = 0;
	num = 0;
	sign = 1;
	while (str[pos] && (str[pos] == '\n' || str[pos] == ' ' || str[pos] == '\t' \
			|| str[pos] == '\r' || str[pos] == '\v' || str[pos] == '\f'))
		pos++;
	if (str[pos] == '-' && str[pos])
	{
		sign = -1;
		pos++;
	}
	else if (str[pos] == '+')
		pos++;
	while (str[pos] >= '0' && str[pos] <= '9')
		num = num * 10 + (str[pos++] - 48);
	return (num * sign);
}
