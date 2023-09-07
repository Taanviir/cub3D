/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:50:10 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 13:01:53 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Writes the integer 'n' to the given file descriptor.
 *
 * @param n The integer to write.
 * @param fd The file descriptor to write to.
 */
void	ft_putnbr_fd(int n, int fd)
{
	int	d;

	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n == -2147483648)
		write(fd, "2147483648", 10);
	else if (n <= 9)
	{
		d = '0' + n;
		write(fd, &d, 1);
	}
	else
	{
		d = n % 10 + '0';
		ft_putnbr_fd(n /= 10, fd);
		write(fd, &d, 1);
	}
}
