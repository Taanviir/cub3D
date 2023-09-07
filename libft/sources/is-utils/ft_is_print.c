/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:53:46 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 12:43:09 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if the given character is a printable ASCII character.
 *
 * @param c The character to be checked.
 * @return true if 'c' is a printable character, false otherwise.
 */
bool	ft_is_print(int c)
{
	return (c >= 32 && c <= 126);
}
