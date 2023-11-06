/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:45:11 by tanas             #+#    #+#             */
/*   Updated: 2023/11/06 15:33:59 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* ------------------------------- error utils ------------------------------ */

/**
 * @brief writes an error message
 *
 * @param error_msg message to write to stderr
 *
 * @return returns 0
 * */
int	write_error_msg(char *error_msg)
{
	ft_putendl_fd("Error:", 2);
	ft_putendl_fd(error_msg, 2);
	return (0);
}

/* -------------------------------- map utils ------------------------------- */
void	print_t_map(t_map *map)
{
	if (!map)
		return ;
	printf("----------GRID------------\n");
	for(int i = 0; i < map->n_rows; i++)
		printf("%s", map->grid[i]);
	printf("\n--------TEXTURES----------\n");
	printf("NO_texture_fd = %d\n", map->NO_texture_fd);
	printf("SO_texture_fd = %d\n", map->SO_texture_fd);
	printf("WE_texture_fd = %d\n", map->WE_texture_fd);
	printf("EA_texture_fd = %d\n", map->EA_texture_fd);
	printf("---------COLORS-----------\n");
	printf("floor	[R] = %d\n", map->f_color[R]);
	printf("floor	[G] = %d\n", map->f_color[G]);
	printf("floor	[B] = %d\n", map->f_color[B]);
	printf("ceiling [R] = %d\n", map->c_color[R]);
	printf("ceiling [G] = %d\n", map->c_color[G]);
	printf("ceiling [B] = %d\n", map->c_color[B]);
}
