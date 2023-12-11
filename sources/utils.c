/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:45:11 by tanas             #+#    #+#             */
/*   Updated: 2023/12/07 15:21:59 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/* ------------------------------- error utils ------------------------------ */

/**
 * @brief writes an error message
 *
 * @param error_msg message to write to stderr
 *
 * @return returns 0
 *
 */
int	write_error_msg(char *error_msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(error_msg, 2);
	return (0);
}

void	my_pixel_put(t_img *image, int x, int y, int color)
{
	if (y >= 0 && x >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
		*(unsigned int *)(image->addr + \
			(y * image->line_length + x * (image->bpp >> 3))) = color;
}
