/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cleanup_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:37:06 by tanas             #+#    #+#             */
/*   Updated: 2023/12/10 13:37:42 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/**
 * @brief Frees all dynamically allocated resources associated with the given
 * t_map structure.
 *
 * @param map A pointer to the t_map structure whose resources are to be freed.
 *
 * @return null
 */
void	map_free(t_map *map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (i < TOTAL_TEXTURES)
			free(map->texture[i++]);
		ft_free_double((void **)map->grid);
		free(map);
		map = NULL;
	}
	exit(FAILURE);
}

/**
 * @brief Clears the buffer used by the get_next_line (gnl) function to prevent
 * memory leaks.
 *
 * This function is needed because gnl retains a portion of the file in a
 * static variable, which can lead to a memory leak if the file is not
 * completely read.
 *
 * @param current_map_row Pointer to the current line being read from the file.
 * @param map_fd File descriptor of the map file.
 */
static void	empty_gnl(char *current_map_row, int map_fd)
{
	while (current_map_row)
	{
		free(current_map_row);
		current_map_row = get_next_line(map_fd);
	}
}

/**
 * @brief Performs full clean-up, freeing and closing map_fd
 *
 * @param current_map_row The current row for use in empty_gnl
 * @param map_fd The map's open fd for closing
 * @param map A pointer to the map struct
 *
 * @return null
 */
void	*map_cleanup(char *current_map_row, int map_fd, t_map *map)
{
	empty_gnl(current_map_row, map_fd);
	close(map_fd);
	map_free(map);
	return (NULL);
}
