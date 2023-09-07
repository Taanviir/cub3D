/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:48:03 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 13:03:22 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Writes the string 's' to the given file descriptor.
 *
 * @param s The string to write.
 * @param fd The file descriptor to write to.
 */
void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		while (*s)
			write(fd, s++, 1);
}
