/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 20:31:45 by tanas             #+#    #+#             */
/*   Updated: 2023/12/10 13:37:48 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/* ------------------------------ main function ----------------------------- */
t_map			*map_load(char *map_path);
/* ----------------------------- initialization ----------------------------- */
static void		map_init_colors(t_map *map);
static t_map	*map_init(void);

/* -------------------------------------------------------------------------- */
/*                                  Load Map                                  */
/* -------------------------------------------------------------------------- */

/**
 * @brief Loads the map data into a t_map structure from the given file path.
 *
 * @param map_path The path of the map file to be loaded.
 *
 * @return A pointer to the populated t_map structure, or NULL if any error
 * occurs (e.g., file not found, memory allocation failure, etc.)
 */
t_map	*map_load(char *map_path)
{
	t_map	*map;
	char	*current_map_row;
	int		map_fd;

	if (!map_extension_check(map_path, ".cub"))
		return (NULL);
	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		return (write_error_msg(OPEN_FAIL), NULL);
	map = map_init();
	if (!map)
		return (close(map_fd), NULL);
	if (!scene_load(map, map_fd, &current_map_row))
		return (map_cleanup(current_map_row, map_fd, map));
	if (!grid_load(map, map_fd, &current_map_row))
		return (map_cleanup(current_map_row, map_fd, map));
	return (close(map_fd), map);
}

/* ----------------------------- initialization ----------------------------- */

/**
 * @brief Initializes the color arrays in the t_map structure to an invalid
 * initial value.
 *
 * This function sets all the elements of `f_color` and `c_color` arrays in
 * the t_map structure to NOT_SET. These are later checked to see if they have
 * been set.
 *
 * @param map A pointer to the t_map structure containing the color arrays to
 * be initialized.
 *
 * @return (SUCCESS);
 */
static void	map_init_colors(t_map *map)
{
	int	i;

	i = 0;
	while (i < TOTAL_COLORS)
		map->f_color[i++] = NOT_SET;
	i = 0;
	while (i < TOTAL_COLORS)
		map->c_color[i++] = NOT_SET;
}

/**
 * @brief Initializes a new t_map structure with initial capacity.
 *
 * Allocates memory for the t_map structure and its grid array. Sets the
 * initial row count to 0 and the initial grid capacity to MAP_INITIAL_CAPACITY.
 *
 * @return A pointer to the initialized t_map structure, or NULL if
 * memory allocation fails.
 */
static t_map	*map_init(void)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (write_error_msg(MALLOC_FAIL), NULL);
	map_init_colors(map);
	map->grid_capacity = MAP_INITIAL_CAPACITY;
	map->grid = ft_calloc(map->grid_capacity + 1, sizeof(char *));
	if (!map->grid)
	{
		free(map);
		return (write_error_msg(MALLOC_FAIL), NULL);
	}
	return (map);
}
