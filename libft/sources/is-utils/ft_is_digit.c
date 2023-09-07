/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_digit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 09:28:15 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 12:42:36 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if the given character is a digit (0-9).
 *
 * @param c The character to be checked.
 * @return true if 'c' is a digit, false otherwise.
 */
bool	ft_is_digit(int c)
{
	return (c >= '0' && c <= '9');
}
