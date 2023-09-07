/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:48:17 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 13:01:13 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Writes the character 'c' to the given file descriptor.
 *
 * @param c The character to write.
 * @param fd The file descriptor to write to.
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
