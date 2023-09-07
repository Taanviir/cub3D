/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placeholders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 13:38:49 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 13:38:49 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Prints a single character to the standard output.
 *
 * @param c The character to be printed.
 * @return The number of characters printed (always 1).
 */
int	ft_print_char(const char c)
{
	return (write(1, &c, 1));
}

/**
 * @brief Prints a string to the standard output.
 *
 * @param str The input string to be printed.
 * @return The number of characters printed (excluding the null terminator).
 */
int	ft_print_string(char *str)
{
	if (!str)
		return (write(1, "(null)", 6));
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

/**
 * @brief Prints a hexadecimal number to the standard output using the
 * specified base.
 *
 * @param n The unsigned integer to be printed as hexadecimal.
 * @param base The base string used for hexadecimal conversion
 * (must be at least 16 characters).
 * @return The number of characters printed.
 */
int	ft_print_hex(unsigned int n, char *base)
{
	int	length_of_print;

	length_of_print = 0;
	if (n > 15)
		length_of_print += ft_print_hex(n / 16, base);
	length_of_print += write(1, &base[n % 16], 1);
	return (length_of_print);
}

/**
 * @brief Prints a signed integer to the standard output.
 *
 * @param n The integer to be printed.
 * @return The number of characters printed.
 */
int	ft_print_number(int n)
{
	char	*number_as_string;
	int		length_of_print;

	number_as_string = ft_itoa(n);
	length_of_print = ft_print_string(number_as_string);
	free(number_as_string);
	return (length_of_print);
}

/**
 * @brief Prints a memory pointer (address) as a hexadecimal number
 * to the standard output.
 *
 * @param pointer The memory pointer (address) to be printed.
 * @param base The base string used for hexadecimal conversion
 * (at least 16 characters).
 * @return The number of characters printed.
 */
int	ft_print_pointer(size_t pointer, char *base)
{
	int	length_of_print;

	length_of_print = 0;
	if (pointer > 15)
		length_of_print += ft_print_pointer(pointer / 16, base);
	length_of_print += write(1, &base[pointer % 16], 1);
	return (length_of_print);
}
