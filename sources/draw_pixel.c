/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:46:40 by tanas             #+#    #+#             */
/*   Updated: 2023/11/18 19:52:52 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_pixel_put(t_img *image, int x, int y, int color)
{
	if (y >= 0 && x >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
		*(unsigned int *)(image->addr + \
			(y * image->line_length + x * (image->bpp / 8))) = color;
}

