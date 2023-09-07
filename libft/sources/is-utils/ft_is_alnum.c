/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_alnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:46:59 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 12:38:15 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if the given character is alphanumeric.
 *
 * @param c The character to be checked.
 * @return true (1) if the character is alphanumeric, false (0) otherwise.
 */
bool	ft_is_alnum(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
		|| (c >= '0' && c <= '9'));
}
