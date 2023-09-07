/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placeholders2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 13:41:53 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 13:41:53 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Calculates the number of digits in an unsigned long integer.
 *
 * @param n The unsigned long integer.
 * @return The number of digits in the integer.
 */
static int	int_length(unsigned long n)
{
	size_t	length;

	length = 0;
	if (n == 0)
		length++;
	while (n > 0)
	{
		n /= 10;
		length++;
	}
	return (length);
}

/**
 * @brief Converts an unsigned integer to a string.
 *
 * @param num The unsigned integer to be converted.
 * @return The string representation of the integer.
 */
static char	*ft_itoa_unsigned(unsigned int num)
{
	char	*str;
	int		length;

	length = int_length(num);
	str = malloc(length + 1);
	if (!str)
		return (NULL);
	str[length--] = '\0';
	if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[length--] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}

int	ft_print_unsigned(unsigned int n)
{
	int		length_of_print;
	char	*number_as_string;

	length_of_print = 0;
	if (n == 0)
		return (write(1, "0", 1));
	number_as_string = ft_itoa_unsigned(n);
	length_of_print = ft_print_string(number_as_string);
	free(number_as_string);
	return (length_of_print);
}
