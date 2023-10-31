/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 22:31:56 by sabdelra          #+#    #+#             */
/*   Updated: 2023/10/26 02:33:25by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


/**
 * @brief Checks if a given cell in the map grid is enclosed by walls ('1') or not.
 *
 * Starting from a given cell specified by its coordinates (x, y), the function uses recursion to traverse the neighboring cells. If it encounters a cell with a value other than '1' or 'V', it returns false.
 *
 * @param map A pointer to the t_map structure that contains the grid to be checked.
 * @param x The x-coordinate of the starting cell.
 * @param y The y-coordinate of the starting cell.
 *
 * @return Returns true if the starting cell is completely enclosed by '1', else returns false.
 */
bool	map_is_enclosed(t_map *map, int x, int y)
{
	char	*current_cell;
	if (x >= (int)ft_strlen(map->grid[y]))
		return (false);
	if (x < 0 || y < 0 || y >= map->n_rows)
		return (false);
	current_cell = &map->grid[y][x];
	if (*current_cell == '1' || *current_cell == 'V')
		return (true);
	else if (*current_cell == '0' || *current_cell == 'S')
		*current_cell = 'V';
	else if (x == 0 || *current_cell == '\n'
		|| ft_is_whitespace(*current_cell)
		|| y == 0 || y == map->n_rows - 1)
		return (false);
	if (map_is_enclosed(map, x + 1, y) == false)
		return (false);
	if (map_is_enclosed(map, x - 1, y) == false)
		return (false);
	if (map_is_enclosed(map, x, y + 1) == false)
		return (false);
	if (map_is_enclosed(map, x, y - 1) == false)
		return (false);
	return (true);
}
