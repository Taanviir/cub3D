/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_validate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:45:12 by sabdelra          #+#    #+#             */
/*   Updated: 2023/11/06 01:02:28 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file map_grid_validation.c
 *
 * @brief Grid Validation for Game Map
 *
 * This file implements the grid validation logic for a game map. It includes functions to:
 * - Check if the map grid is enclosed by walls.
 * - Validate the characters in the map grid against a set of accepted characters.
 * - Ensure there is exactly one player spawn point.
 *
 * These functions are used to validate the integrity of the map layout before the game starts, ensuring
 * that the environment is set up correctly and is ready for gameplay.
 */

#include "cub3D.h"

static bool	grid_is_enclosed(t_map *map, int x, int y);
static bool	grid_validate_characters(t_map *map);

/**
 * @brief Validates the entire map grid for a game level.
 *
 * This function orchestrates the validation of the game map by first checking if all characters within the grid are valid
 * and then ensuring the map's integrity by verifying that it's fully enclosed. It acts as the final step in the map
 * validation process, aggregating checks for character correctness and structural enclosure.
 *
 * @param map A pointer to the t_map structure that represents the map to be validated.
 *
 * @return true if the map grid passes all validation checks, otherwise false.
 */
bool	map_grid_validate(t_map *map)
{
	int	x;
	int	y;

	if (!grid_validate_characters(map))
		return (false);
	x = map->player.x_coord;
	y = map->player.y_coord;
	if (!grid_is_enclosed(map, x, y))
		return (write_error_msg(MAP_NOT_ENCLOSED));
	return (true);
}

/**
 * @brief Checks if a given cell in the map grid is enclosed by walls ('1') or not.
 *
 * Starting from the players position specified by its coordinates (x, y), the function uses recursion to traverse the neighboring cells.
 *
 * @param map A pointer to the t_map structure.
 * @param x The initial x-coordinate of the player.
 * @param y The initial y-coordinate of the player.
 *
 * @return Returns true if the starting cell is completely enclosed by '1', else returns false.
 * @note the grid cell value is changed to V, to indicate visited
 */
static bool	grid_is_enclosed(t_map *map, int x, int y)
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
	if (grid_is_enclosed(map, x + 1, y) == false)
		return (false);
	if (grid_is_enclosed(map, x - 1, y) == false)
		return (false);
	if (grid_is_enclosed(map, x, y + 1) == false)
		return (false);
	if (grid_is_enclosed(map, x, y - 1) == false)
		return (false);
	return (true);
}

/**
 * @brief Validates the characters in the map grid and ensures only one player exists.
 *
 * This function iterates over each row and column of the map grid, checking for valid characters according
 * to the defined character set. It also counts the number of player characters to ensure there is exactly one
 * player on the map.
 *
 * @param map A pointer to the t_map structure containing the grid.
 *
 * @return true if the grid contains only valid characters and one player, false otherwise.
 */
static bool	grid_validate_characters(t_map *map)
{
	int	x;
	int	y;
	int	player_count;

	y = 0;
	player_count = 0;
	while (y < map->n_rows)
	{
		x = 0;
		while (map->grid[y][x] != '\n')
		{
			if (ft_strchr(PLAYER_DIRECTIONS, map->grid[y][x]))
			{
				map->player.x_coord = x;
				map->player.y_coord = y;
				player_count++;
			}
			if (!ft_strchr(ACCEPTED_CHARACTERS, map->grid[y][x]))
				return (write_error_msg(MAP_INVALID_CHARACTER));
			x++;
		}
		y++;
	}
	if (player_count != 1)
		return (write_error_msg(INVALID_PLAYER_COUNT));
	return (true);
}
