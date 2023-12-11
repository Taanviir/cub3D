/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:24:22 by tanas             #+#    #+#             */
/*   Updated: 2023/12/11 12:59:48 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

#define COLOR_START 2
#define PATH_START 3 //path should start after the 3rd character of the map row

/**
 * @brief Sets the color components of a map using the information from the
 * current row of the map file.
 *
 * Parses the color string into individual RGB components and updates the
 * corresponding color variables in the map.
 *
 * @param map_color A pointer to an array of integers representing the
 * RGB color values for the map.
 * @param current_map_row A pointer to the current line in the map file,
 * which contains the color information.
 *
 * @return An integer indicating success (SUCCESS) or failure (FAILURE).
 */
static int	scene_set_color(int *map_color, char *current_map_row)
{
	char	*color_string;
	char	**rgb_color_strings;
	int		i;
	int		status;

	i = -1;
	status = SUCCESS;
	color_string = ft_substr(current_map_row, COLOR_START,
			ft_strlen(current_map_row) - COLOR_START);
	if (!scene_validate_color(color_string))
		return (FAILURE);
	rgb_color_strings = ft_split(color_string, ',');
	while (++i < TOTAL_COLORS)
	{
		if (!rgb_color_strings[i])
			break ;
		map_color[i] = ft_atoi(rgb_color_strings[i]);
		if (map_color[i] > 255 || map_color[i] < 0)
			status = FAILURE;
	}
	ft_free_double((void **)rgb_color_strings);
	free(color_string);
	if (status)
		free(current_map_row);
	return (status);
}

/**
 * @brief Sets the file descriptor for a texture based on its path extracted
 * from the current map row.
 *
 * This function extracts the texture path from the current map row starting at
 * index 3, then attempts to open the file to set the file descriptor.
 * It also handles failures by writing an error message.
 *
 * @param texture A pointer to the file_path to be set
 * @param current_map_row A pointer to the string containing the current map
 * row from which the texture path is to be extracted.
 *
 * @return true, if pass failed if not
 */
static bool	scene_set_texture(char **texture, char *current_map_row)
{
	*texture = ft_substr(current_map_row, PATH_START,
			ft_strlen(current_map_row) - PATH_START);
	if (!map_extension_check(*texture, ".xpm"))
		return (FAILURE);
	free(current_map_row);
	if (*texture == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

/**
 * @brief Configures the scene settings for the map based on the texture and
 * color identifiers.
 *
 * This function sets the textures and colors based on the identifier string
 * provided. It calls appropriate helper functions to handle the actual
 * setting of values.
 *
 * @param map A pointer to the t_map structure where the scene settings will
 * be stored.
 * @param texture_id A pointer to the string identifier for the texture or
 * color.
 * @param current_map_row A pointer to the current line in the map file,
 * containing texture or color information.
 *
 * @return An integer indicating success (SUCCESS) or failure (FAILURE).
 */
static int	scene_set(t_map *map, char *texture_id, char *current_map_row)
{
	if (!ft_strncmp(texture_id, "NO", 2) && !map->texture[NO])
		return (scene_set_texture(&map->texture[NO], current_map_row));
	else if (!ft_strncmp(texture_id, "SO", 2) && !map->texture[SO])
		return (scene_set_texture(&map->texture[SO], current_map_row));
	else if (!ft_strncmp(texture_id, "WE", 2) && !map->texture[WE])
		return (scene_set_texture(&map->texture[WE], current_map_row));
	else if (!ft_strncmp(texture_id, "EA", 2) && !map->texture[EA])
		return (scene_set_texture(&map->texture[EA], current_map_row));
	else if (!ft_strncmp(texture_id, "F", 1) && map->f_color[0] == NOT_SET)
		return (scene_set_color(map->f_color, current_map_row));
	else if (!ft_strncmp(texture_id, "C", 1) && map->c_color[0] == NOT_SET)
		return (scene_set_color(map->c_color, current_map_row));
	else
		return (FAILURE);
}

/**
 * @brief Verifies that all color components for the floor and ceiling have
 * been properly set.
 *
 * This function iterates through the arrays for floor and ceiling colors in
 * the t_map structure, checking to ensure that none of the color components
 * have been left unset.
 *
 * @param map A pointer to the t_map structure containing the color settings.
 *
 * @return An integer indicating success (SUCCESS) or failure (FAILURE).
 */
static int	scene_verify_colors(t_map *map)
{
	int	i;

	i = 0;
	while (i < TOTAL_COLORS)
	{
		if (map->f_color[i++] == NOT_SET)
			return (FAILURE);
	}
	i = 0;
	while (i < TOTAL_COLORS)
	{
		if (map->c_color[i++] == NOT_SET)
			return (FAILURE);
	}
	return (SUCCESS);
}

/**
 * @brief Loads scene-related settings for the map.
 *
 * This function reads lines from the file descriptor until it encounters
 * either an empty row or a row that doesn't begin with an alphabetic character.
 * It then tries to set scene-related parameters (textures and colors)
 * based on the read lines.
 *
 * @param map A pointer to the t_map structure where the scene data will be
 * stored.
 * @param map_fd File descriptor from which the map data is read.
 * @param current_map_row Double pointer to the string that holds the current
 * map row being processed.
 * @return An integer indicating success (SUCCESS) or failure (FAILURE).
 */
int	scene_load(t_map *map, int map_fd, char **current_map_row)
{
	char	*texture_id;

	while (true)
	{
		*current_map_row = map_next_valid_row(map_fd);
		if (!*current_map_row || !ft_is_alpha(*current_map_row[0]))
			break ;
		texture_id = scene_get_texture_id(*current_map_row);
		if (!texture_id)
			return (write_error_msg(SCENE_FAIL));
		if (!scene_set(map, texture_id, *current_map_row))
		{
			free(texture_id);
			return (write_error_msg(SCENE_FAIL));
		}
		free(texture_id);
	}
	if (!map->texture[NO] || !map->texture[SO] || !map->texture[WE]
		|| !map->texture[EA] || !scene_verify_colors(map))
		return (write_error_msg(SCENE_FAIL));
	return (SUCCESS);
}
