/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_ascii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:49:05 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 12:42:23 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if the given character is an ASCII character.
 *
 * @param c The character to be checked.
 * @return true if 'c' is an ASCII character, false otherwise.
 */
bool	ft_is_ascii(int c)
{
	return (c >= 0 && c <= 127);
}
