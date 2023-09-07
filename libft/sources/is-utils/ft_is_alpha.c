/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_alpha.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:41:08 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 12:41:26 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if the given character is an alphabet (uppercase or lowercase).
 *
 * @param c The character to be checked.
 * @return true if 'c' is an alphabet letter, false otherwise.
 */
bool	ft_is_alpha(int c)
{
	return ((c >= 'a' && c <= 'z') || ((c >= 'A' && c <= 'Z')));
}
