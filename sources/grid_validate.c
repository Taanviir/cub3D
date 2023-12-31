/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_validate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:45:12 by sabdelra          #+#    #+#             */
/*   Updated: 2023/12/10 00:53:49 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file map_grid_validation.c
 *
 * @brief Grid Validation for Game Map
 *
 * This file implements the grid validation logic for a game map.
 * It includes functions to:
 * - Check if the map grid is enclosed by walls.
 * - Validate the characters in the map grid against a set of accepted
 *   characters.
 * - Ensure there is exactly one player spawn point.
 *
 * These functions are used to validate the integrity of the map layout
 * before the game starts, ensuring that the environment is set up correctly
 * and is ready for gameplay.
 */

#include "../includes/cub3D.h"

static bool	grid_is_enclosed(const t_map *map, const int x, const int y);
static bool	grid_validate_characters(t_map *map, t_player *player);
static void	create_player(t_player *player, int x, int y, char view_direction);

/**
 * @brief Validates the entire map grid for a game level.
 *
 * This function orchestrates the validation of the game map by first checking
 * if all characters within the grid are valid and then ensuring the map's
 * integrity by verifying that it's fully enclosed. It acts as the final
 * step in the map validation process, aggregating checks for character
 * correctness and structural enclosure.
 *
 * @param map A pointer to the t_map structure that represents the map to be
 * validated.
 *
 * @return true if the map grid passes all validation checks, otherwise false.
 */
t_map	*grid_validate(t_map *map, t_player *player)
{
	if (!grid_validate_characters(map, player))
		map_free(map);
	if (!grid_is_enclosed(map, player->pos[X], player->pos[Y]))
	{
		write_error_msg(MAP_NOT_ENCLOSED);
		map_free(map);
	}
	return (map);
}

/**
 * @brief Checks if a given cell in the map grid is enclosed by walls ('1')
 * or not.
 *
 * Starting from the players position specified by its coordinates (x, y),
 * the function uses recursion to traverse the neighboring cells.
 *
 * @param map A pointer to the t_map structure.
 * @param x The initial x-coordinate of the player.
 * @param y The initial y-coordinate of the player.
 *
 * @return Returns true if the starting cell is completely enclosed by '1',
 * else returns false.
 * @note the grid cell value is changed to V, to indicate visited
 */
static bool	grid_is_enclosed(const t_map *map, const int x, const int y)
{
	char	*current_cell;

	if (x >= (int)ft_strlen(map->grid[y]) || x < 0 || y < 0 || y >= map->n_rows)
		return (FAILURE);
	current_cell = &map->grid[y][x];
	if (*current_cell == WALL || *current_cell == 'V')
		return (true);
	else if (*current_cell == '0'
		|| ft_strchr(PLAYER_DIRECTIONS, *current_cell))
		*current_cell = 'V';
	else if (x == 0 || *current_cell == '\n'
		|| ft_is_whitespace(*current_cell)
		|| y == 0 || y == map->n_rows - 1)
		return (FAILURE);
	if (!grid_is_enclosed(map, x + 1, y) || !grid_is_enclosed(map, x - 1, y)
		|| !grid_is_enclosed(map, x, y + 1) || !grid_is_enclosed(map, x, y - 1))
		return (FAILURE);
	return (true);
}

/**
 * @brief Validates map grid for character integrity and initializes player.
 *
 * Iterates over the map grid to ensure all characters are valid and
 * locates the player's position and direction, enforcing a single player rule.
 *
 * @param map A pointer to the t_map structure containing the grid.
 *
 * @return true if the grid passes validation with one player present,
 * false otherwise.
 */
static bool	grid_validate_characters(t_map *map, t_player *player)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	y = -1;
	while (++y < map->n_rows)
	{
		x = -1;
		while (map->grid[y][++x])
		{
			if (ft_strchr(PLAYER_DIRECTIONS, map->grid[y][x]))
			{
				create_player(player, x, y, map->grid[y][x]);
				player_count++;
			}
			if (!ft_strchr(ACCEPTED_CHARACTERS, map->grid[y][x]))
				return (write_error_msg(MAP_INVALID_CHARACTER));
		}
	}
	if (player_count != 1)
		return (write_error_msg(INVALID_PLAYER_COUNT));
	return (true);
}

static void	create_player(t_player *player, int x, int y, char view_direction)
{
	player->pos[X] = x + 0.5;
	player->pos[Y] = y + 0.5;
	if (view_direction == 'E')
	{
		player->direction[X] = 1;
		player->camera_plane[Y] = 0.66;
	}
	else if (view_direction == 'W')
	{
		player->direction[X] = -1;
		player->camera_plane[Y] = -0.66;
	}
	else if (view_direction == 'N')
	{
		player->direction[Y] = -1;
		player->camera_plane[X] = 0.66;
	}
	else if (view_direction == 'S')
	{
		player->direction[Y] = 1;
		player->camera_plane[X] = -0.66;
	}
	else
		write_error_msg(MAP_INVALID_CHARACTER);
}
