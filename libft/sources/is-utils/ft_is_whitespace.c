/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_whitespace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:58:01 by codespace         #+#    #+#             */
/*   Updated: 2023/07/29 12:41:43 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if the given character is a whitespace character.
 *
 * This function checks for space (' '), tab ('\t'), carriage return ('\r'),
 * newline ('\n'), and vertical tab ('\v') characters.
 *
 * @param c The character to be checked.
 * @return true if 'c' is a whitespace character, false otherwise.
 */
bool	ft_is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v');
}
