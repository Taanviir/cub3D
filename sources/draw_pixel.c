/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:46:40 by tanas             #+#    #+#             */
/*   Updated: 2023/11/14 01:19:16 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_pixel_put(t_img *img_data, int x, int y, int color)
{
	if (y >= 0 && x >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
		*(unsigned int *)(img_data->addr + \
			(y * img_data->line_length + x * (img_data->bpp / 8))) = color;
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	draw_line(t_img *img_data, t_point a, t_point b)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int err2;

	dx = ft_abs(b.x - a.x);
	dy = ft_abs(b.y - a.y);
	if (a.x < b.x)
		sx = 1;
	else
		sx = -1;
	if (a.y < b.y)
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	while (1)
	{
		my_pixel_put(img_data, a.x, a.y, 0x00ff00);
		if (a.x == b.x && a.y == b.y)
			break ;
		err2 = 2 * err;
		if (err2 > -dy)
		{
			err -= dy;
			a.x = a.x + sx;
		}
		if (err2 < dx)
		{
			err += dx;
			a.y = a.y + sy;
		}
	}
}
