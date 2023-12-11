/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 12:39:08 by tanas             #+#    #+#             */
/*   Updated: 2023/12/10 12:41:43 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/**
 * @brief Resizes the grid array in the t_map structure to double its
 * current row capacity.
 *
 * @param map A pointer to the t_map structure that holds the grid to be
 * resized.
 *
 * @return SUCCESS if the resizing is successful, FAILURE otherwise
 * (e.g., memory allocation failure).
 */
static int	grid_resize(t_map *map)
{
	char	**old_grid;
	int		row_index;

	row_index = 0;
	old_grid = map->grid;
	map->grid_capacity *= DOUBLE;
	map->grid = ft_calloc(map->grid_capacity + 1, sizeof(char *));
	if (!map->grid)
	{
		write_error_msg(MALLOC_FAIL);
		return (FAILURE);
	}
	while (row_index < map->n_rows)
	{
		map->grid[row_index] = old_grid[row_index];
		row_index++;
	}
	free(old_grid);
	return (SUCCESS);
}

/**
 * @brief Adds a row to the grid array in the t_map structure.
 *
 * Resizes the grid array if its current capacity is reached before adding
 * the row.
 *
 * @param current_map_row The row data to add.
 * @param map A pointer to the t_map structure that holds the grid to be
 * modified.
 *
 * @return SUCCESS if the row is successfully added, FAILURE otherwise
 * (e.g., resizing failure).
 */
static int	grid_add_row(char *current_map_row, t_map *map)
{
	if (!current_map_row)
		return (FAILURE);
	if (map->n_rows == map->grid_capacity)
	{
		if (!grid_resize(map))
			return (FAILURE);
	}
	map->grid[map->n_rows++] = current_map_row;
	return (SUCCESS);
}

/**
 * @brief Reads the grid data from the map file descriptor and populates the
 * t_map structure.
 *
 * @param map A pointer to the t_map structure to populate.
 * @param map_fd The file descriptor of the map to read from.
 * @param current_map_row a double pointer of the current map row
 *
 * @return SUCCESS if the grid is read and populated successfully, FAILURE
 * otherwise.
 */
int	grid_load(t_map *map, int map_fd, char **current_map_row)
{
	while (*current_map_row)
	{
		if (!grid_add_row(*current_map_row, map))
			return (FAILURE);
		*current_map_row = get_next_line(map_fd);
	}
	return (SUCCESS);
}
