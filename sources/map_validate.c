/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 22:31:56 by sabdelra          #+#    #+#             */
/*   Updated: 2023/10/25 22:33:21 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
/* -------------------------------- flood map ------------------------------- */
int	map_validate(t_map *map, int sp_x, int sp_y)
{
	char	*current_location;

	if (sp_x < 0 || sp_y < 0 || sp_y >= map->n_rows)
		return (-1);
	current_location = &map->grid[sp_y][sp_x];
	if (*current_location == '1' || *current_location == 'V')
		return (1);
	else if (*current_location == '0' || *current_location == 'S')
		*current_location = 'V';
	else if (sp_x == 0 || *current_location == '\n'
		|| ft_is_whitespace(*current_location)
		|| sp_y == 0 || sp_y == map->n_rows - 1)
		return (-1);
	if (map_validate(map, sp_x + 1, sp_y) == -1)
		return (-1);
	if (map_validate(map, sp_x - 1, sp_y) == -1)
		return (-1);
	if (map_validate(map, sp_x, sp_y + 1) == -1)
		return (-1);
	if (map_validate(map, sp_x, sp_y - 1) == -1)
		return (-1);
	return (1);
}
