/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:28:45 by tanas             #+#    #+#             */
/*   Updated: 2023/12/10 13:38:13 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/**
 * @brief Extracts the texture identifier from the current map row.
 *
 * This function scans the current map row to find a texture identifier which
 * is either one or two characters long and terminated by a space. If such an
 * identifier is found, it is returned as a substring.
 *
 * @param current_map_row A pointer to the string containing the current map
 * row from which the texture identifier is to be extracted.
 * @return A pointer to the substring containing the texture identifier, or
 * NULL if the identifier is invalid.
 */
char	*scene_get_texture_id(char *current_map_row)
{
	int	id_length;

	id_length = 0;
	while (current_map_row[id_length] && current_map_row[id_length] != ' ')
		id_length++;
	if (id_length != 2 && id_length != 1)
		return (FAILURE);
	return (ft_substr(current_map_row, 0, id_length));
}

/**
 * @brief Validates if a given string is a valid representation of a color.
 *
 * This function checks that each character in the string is either a digit or
 * a comma, ensuring that it can be safely used as a color specification string.
 *
 * @param color_string A pointer to the string that needs to be validated.
 *
 * @return An integer indicating success (SUCCESS) or failure (FAILURE).
 */
int	scene_validate_color(char *color_string)
{
	size_t	i;
	size_t	comma_counter;

	i = 0;
	comma_counter = 0;
	if (!color_string || !*color_string)
		return (FAILURE);
	while (color_string[i])
	{
		if (color_string[i] == ',')
			comma_counter++;
		if (!ft_is_digit(color_string[i])
			&& color_string[i] != ',')
			return (FAILURE);
		i++;
	}
	if (comma_counter != 2)
		return (FAILURE);
	return (SUCCESS);
}

/**
 * @brief Checks if a given line contains only whitespace characters.
 *
 * @param current_map_row The line to check.
 * @return true if the line contains only whitespace characters, false
 * otherwise.
 */
static bool	map_row_is_empty(char *current_map_row)
{
	while (current_map_row && *current_map_row)
	{
		if (!ft_is_whitespace(*current_map_row) && *current_map_row != '\n')
			break ;
		else
			current_map_row++;
	}
	if (current_map_row && *current_map_row)
		return (false);
	return (true);
}

/**
 * @brief Reads lines from a map file until a non-empty row is found.
 *
 * Reads and discards all empty rows, returning the first non-empty row
 * encountered.
 *
 * @param map_fd The file descriptor of the map to read from.
 *
 * @return A pointer to the first non-empty row found, or NULL if EOF is
 * reached.
 *
 * @note currently only nulling the scene lines, maybe also null the grid?
 */
char	*map_next_valid_row(int map_fd)
{
	char	*current_map_row;

	current_map_row = ft_calloc(1, sizeof(char *));
	while (current_map_row && map_row_is_empty(current_map_row))
	{
		free(current_map_row);
		current_map_row = get_next_line(map_fd);
	}
	if (current_map_row && ft_is_alpha(current_map_row[0]))
		current_map_row[ft_strlen(current_map_row) - 1] = '\0';
	return (current_map_row);
}

/**
 * @brief Checks if the file extension of the given map path is '.cub'.
 *
 * This function verifies that the map file has the '.cub' extension. If not,
 * it prints an extension error message.
 *
 * @param map_path Pointer to the path of the map file.
 * @return true if the file has a '.cub' extension, false otherwise.
 */
bool	map_extension_check(char *map_path, char *target)
{
	char	*extension;

	if (!map_path)
		return (write_error_msg(EXTENSION_ERROR));
	extension = ft_strrchr(map_path, '.');
	if (!extension)
		return (write_error_msg(EXTENSION_ERROR));
	if (ft_strncmp(extension, target, ft_strlen(target)))
		return (write_error_msg(EXTENSION_ERROR));
	else
		return (true);
}
