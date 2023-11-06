#include "cub3D.h"

/* -------------------------------------------------------------------------- */
/*                                    BUGS                                    */
/* -------------------------------------------------------------------------- */

/* ------------------------------ main function ----------------------------- */
t_map			*map_load(char *map_path);
/* ----------------------------- initialization ----------------------------- */
static int		verify_open(char *map_path, int options);
static void		map_init_colors(t_map *map);
static t_map	*map_init(void);
/* ---------------------------------- grid ---------------------------------- */
static int		map_resize(t_map *map);
static int		map_add_row(char *row, t_map *map);
static int		map_load_grid(t_map *map, int map_fd, char **current_map_row); //!
/* ---------------------------------- scene --------------------------------- */
static bool		map_row_is_empty(char *current_map_row);
static char		*map_next_valid_row(int map_fd);
static char		*map_get_texture_id(char *current_map_row);
static void		map_set_texture(int	*texture_fd, char *current_map_row);
static bool		validate_color_string(char *color_string);
static void		map_set_color(int *map_color, char *current_map_row);
static int		map_set_scene(t_map *map, char *texture_id, char *current_map_row);
static int		check_colors(t_map *map);
static int		map_load_scene(t_map *map, int map_fd, char **current_map_row);

/* -------------------------------- utilities ------------------------------- */
static void		map_close(t_map *map);
static void		empty_gnl(char *current_map_row, int map_fd);
void			map_free(t_map *map);
bool			map_extension_check(char *map_path);
/* -------------------------------------------------------------------------- */
/*                                  Load Map                                  */
/* -------------------------------------------------------------------------- */

/**
 * @brief Clears the buffer used by the get_next_line (gnl) function to prevent memory leaks.
 *
 * This function is needed because gnl retains a portion of the file in a static variable, which can lead to a memory leak if the file is not completely read.
 *
 * @param current_map_row Pointer to the current line being read from the file.
 * @param map_fd File descriptor of the map file.
 */
static void empty_gnl(char *current_map_row, int map_fd)
{
	while (current_map_row)
	{
		free(current_map_row);
		current_map_row = get_next_line(map_fd);
	}
}

/**
 * @brief Loads the map data into a t_map structure from the given file path.
 *
 * @param map_path The path of the map file to be loaded.
 *
 * @return A pointer to the populated t_map structure, or NULL if any error occurs (e.g., file not found, memory allocation failure, etc.)
 */
t_map	*map_load(char *map_path)
{
	t_map	*map;
	char	*current_map_row;
	int		map_fd;

	map_fd = verify_open(map_path, O_RDONLY);
	if (map_fd == FAILURE)
		return (NULL);
	map = map_init();
	if (!map)
		return (close(map_fd), NULL);
	if (!map_load_scene(map, map_fd, &current_map_row))
	{
		empty_gnl(current_map_row, map_fd);
		close(map_fd);
		map_free(map);
		return (NULL);
	}
	if (!map_load_grid(map, map_fd, &current_map_row))
	{
		empty_gnl(current_map_row, map_fd);
		close(map_fd);
		map_free(map);
		return (NULL);
	}
	close(map_fd);
	return map;
}

/* ----------------------------- initialization ----------------------------- */

/**
 * @brief Opens and verifies a file was opened successfully, prints an error message if not
 *
 * @param file_path The file path to open
 * @param options The options passed to open call
 *
 * @return The file descriptor for the opened file, or 0 if the file cannot be opened.
 */
static int	verify_open(char *file_path, int options)
{
	int	fd;

	fd = open(file_path, options);
	if (fd == -1)
	{
		write_error_msg(OPEN_FAIL);
		ft_putendl_fd(file_path, 2);
		return (FAILURE);
	}
	return (fd);
}

/**
 * @brief Initializes the color arrays in the t_map structure to an invalid initial value.
 *
 * This function sets all the elements of `f_color` and `c_color` arrays in the t_map structure to NOT_SET. These are later checked to see if they have been set.
 *
 * @param map A pointer to the t_map structure containing the color arrays to be initialized.
 */
static void map_init_colors(t_map *map)
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
 * Allocates memory for the t_map structure and its grid array. Sets the initial row count to 0
 * and the initial grid capacity to MAP_INITIAL_CAPACITY.
 *
 * @return A pointer to the initialized t_map structure, or NULL if memory allocation fails.
 */
static t_map	*map_init(void)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
	{
		write_error_msg(MALLOC_FAIL);
		return (NULL);
	}
	map_init_colors(map);
	map->grid_capacity = MAP_INITIAL_CAPACITY;
	map->grid = ft_calloc(map->grid_capacity, sizeof(char *));
	if (!map->grid)
	{
		write_error_msg(MALLOC_FAIL);
		free (map);
		return (NULL);
	}
	return (map);
}

/* ---------------------------------- grid ---------------------------------- */

/**
 * @brief Reads the grid data from the map file descriptor and populates the t_map structure.
 *
 * @param map A pointer to the t_map structure to populate.
 * @param map_fd The file descriptor of the map to read from.
 * @param current_map_row a double pointer of the current map row
 * @return SUCCESS if the grid is read and populated successfully, FAILURE otherwise.
 */
static int	map_load_grid(t_map *map, int map_fd, char **current_map_row)
{
	int	y;
	int	x;

	while (*current_map_row)
	{
		if(!map_add_row(*current_map_row, map))
			return (FAILURE);
		*current_map_row = get_next_line(map_fd);
	}
	y = -1;
	while (++y < map->n_rows) //! THIS PART IS FULLY BROKEN
	{
		x = -1;
		while (map->grid[y][++x])
		{
			if (map->grid[y][x] == '1')
				break ;
		}
		if (map->grid[y][++x] == '1')
			break ;
	}
	if (map_is_enclosed(map, 1, 1))
	// if (map_is_enclosed(map, x, y))
		return (SUCCESS);
	else
		return (write_error_msg(MAP_NOT_ENCLOSED));
}

/**
 * @brief Resizes the grid array in the t_map structure to double its current row capacity.
 *
 * @param map A pointer to the t_map structure that holds the grid to be resized.
 *
 * @return SUCCESS if the resizing is successful, FAILURE otherwise (e.g., memory allocation failure).
 */
static int map_resize(t_map *map)
{
	char	**old_grid;
	int		row_index;

	row_index = 0;
	old_grid = map->grid;
	map->grid_capacity *= DOUBLE;
	map->grid = ft_calloc(sizeof(char *), map->grid_capacity);
	if(!map->grid)
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
 * Resizes the grid array if its current capacity is reached before adding the row.
 *
 * @param current_map_row The row data to add.
 * @param map A pointer to the t_map structure that holds the grid to be modified.
 *
 * @return SUCCESS if the row is successfully added, FAILURE otherwise (e.g., resizing failure).
 */
static int map_add_row(char *current_map_row, t_map *map)
{
	if (!current_map_row)
		return (FAILURE);
	if (map->n_rows == map->grid_capacity)
	{
		if(!map_resize(map))
			return (FAILURE);
	}
	map->grid[map->n_rows++] = current_map_row;
	return (SUCCESS);
}

/* ---------------------------------- scene --------------------------------- */

/**
 * @brief Checks if a given line contains only whitespace characters.
 *
 * @param current_map_row The line to check.
 * @return true if the line contains only whitespace characters, false otherwise.
 */
static bool	map_row_is_empty(char *current_map_row)
{
	while (current_map_row && *current_map_row)
	{
		if (!ft_is_whitespace(*current_map_row) && *current_map_row != '\n')
			break;
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
 * Reads and discards all empty rows, returning the first non-empty row encountered.
 *
 * @param map_fd The file descriptor of the map to read from.
 * @return A pointer to the first non-empty row found, or NULL if EOF is reached.
 */
static char	*map_next_valid_row(int map_fd)
{
	char	*current_map_row;

	current_map_row = ft_calloc(1,1); // hate this fix
	while (current_map_row && map_row_is_empty(current_map_row))
	{
		free(current_map_row);
		current_map_row = get_next_line(map_fd);
	}
	if (current_map_row && ft_is_alpha(current_map_row[0]))
		current_map_row[ft_strlen(current_map_row) - 1] = '\0'; // replace new-line with null
	return (current_map_row);
}

/**
 * @brief Extracts the texture identifier from the current map row.
 *
 * This function scans the current map row to find a texture identifier which is either one or two characters long and terminated by a space. If such an identifier is found, it is returned as a substring.
 *
 * @param current_map_row A pointer to the string containing the current map row from which the texture identifier is to be extracted.
 * @return A pointer to the substring containing the texture identifier, or NULL if the identifier is invalid.
 */
static char	*map_get_texture_id(char *current_map_row)
{
	int	id_length;

	id_length = 0;
	while (current_map_row[id_length] && current_map_row[id_length] != ' ')
		id_length++;
	if (id_length != 2 && id_length != 1)
		return (NULL);
	return (ft_substr(current_map_row, 0, id_length));
}

/**
 * @brief Sets the file descriptor for a texture based on its path extracted from the current map row.
 *
 * This function extracts the texture path from the current map row starting at index 3, then attempts to open the file to set the file descriptor. It also handles failures by writing an error message.
 *
 * @param texture_fd A pointer to the file descriptor to be set.
 * @param current_map_row A pointer to the string containing the current map row from which the texture path is to be extracted.
 */
static void	map_set_texture(int	*texture_fd, char *current_map_row)
{
	char	*texture_path;

	texture_path= ft_substr(current_map_row, 3, ft_strlen(current_map_row) - 3);
	*texture_fd = verify_open(texture_path, O_RDONLY);
	free(current_map_row);
	free(texture_path);
	if (*texture_fd == FAILURE)
		write_error_msg(SCENE_FAIL);
}

/**
 * @brief Validates if a given string is a valid representation of a color.
 *
 * This function checks that each character in the string is either a digit or a comma, ensuring that it can be safely used as a color specification string.
 *
 * @param color_string A pointer to the string that needs to be validated.
 * @return Returns true if the string is a valid representation of a color, otherwise returns false.
 */
static bool validate_color_string(char *color_string)
{
	size_t	i;

	i = 0;
	if (!color_string || !*color_string)
		return (false);
	while (color_string[i])
	{
		if (!ft_is_digit(color_string[i])
			&& color_string[i] != ',')
		return (false);
		i++;
	}
	return (true);
}
/**
 * @brief Sets the color components of a map using the information from the current row of the map file.
 *
 * Parses the color string into individual RGB components and updates the corresponding color variables in the map.
 *
 * @param map_color A pointer to an array of integers representing the RGB color values for the map.
 * @param current_map_row A pointer to the current line in the map file, which contains the color information.
 */
static void	map_set_color(int *map_color, char *current_map_row)
{
	// get color string
	char	*color_string;
	char	**rgb_color_strings;
	int		i;

	i = 0;
	color_string = ft_substr(current_map_row, 2, ft_strlen(current_map_row) - 2); // in the format x[x*],x[x*],x[x*]
	if (!validate_color_string(color_string))
		i = TOTAL_COLORS; // oh god the fixes top kek, nah jk please fix this
	rgb_color_strings = ft_split(color_string, ',');
	while (i < TOTAL_COLORS)
	{
		if (!rgb_color_strings[i])
			break ;
		map_color[i] = ft_atoi(rgb_color_strings[i]);
		if (map_color[i] > 255 || map_color[i] < 0)
		{
			map_color[i] = NOT_SET;
			break;
		}
		i++;
	}
	ft_free_double((void **)rgb_color_strings);
	free(color_string);
	free(current_map_row);
}

/**
 * @brief Configures the scene settings for the map based on the texture and color identifiers.
 *
 * This function sets the textures and colors based on the identifier string provided. It calls appropriate helper functions to handle the actual setting of values.
 *
 * @param map A pointer to the t_map structure where the scene settings will be stored.
 * @param texture_id A pointer to the string identifier for the texture or color.
 * @param current_map_row A pointer to the current line in the map file, containing texture or color information.
 * @return An integer indicating success (SUCCESS) or failure (FAILURE).
 */
static int	map_set_scene(t_map *map, char *texture_id, char *current_map_row)
{
	if (!texture_id)
	{
		write_error_msg(SCENE_FAIL);
		return (FAILURE);
	}
	if (!ft_strncmp(texture_id, "NO", 2))
		map_set_texture(&map->NO_texture_fd, current_map_row);
	else if (!ft_strncmp(texture_id, "SO", 2))
		map_set_texture(&map->SO_texture_fd, current_map_row);
	else if (!ft_strncmp(texture_id, "WE", 2))
		map_set_texture(&map->WE_texture_fd, current_map_row);
	else if (!ft_strncmp(texture_id, "EA", 2))
		map_set_texture(&map->EA_texture_fd, current_map_row);
	else if (!ft_strncmp(texture_id, "F", 1))
		map_set_color(map->f_color, current_map_row);
	else if (!ft_strncmp(texture_id, "C", 1))
		map_set_color(map->c_color, current_map_row);
	else
	{
		write_error_msg(SCENE_FAIL);
		return (FAILURE);
	}
	return (SUCCESS);
}
/**
 * @brief Verifies that all color components for the floor and ceiling have been properly set.
 *
 * This function iterates through the arrays for floor and ceiling colors in the t_map structure,
 * checking to ensure that none of the color components have been left unset.
 *
 * @param map A pointer to the t_map structure containing the color settings.
 * @return An integer indicating success (SUCCESS) or failure (FAILURE).
 */
static int	check_colors(t_map *map)
{
	int	i;

	i = 0;
	while (i < TOTAL_COLORS)
	{
		if (map->f_color[i++] == NOT_SET)
		{
			write_error_msg(COLOR_ERROR);
			return (FAILURE);
		}
	}
	i = 0;
	while (i < TOTAL_COLORS)
	{
		if (map->c_color[i++] == NOT_SET)
		{
			write_error_msg(COLOR_ERROR);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

/**
 * @brief Loads scene-related settings for the map.
 *
 * This function reads lines from the file descriptor until it encounters either an empty row or a row that doesn't
 * begin with an alphabetic character. It then tries to set scene-related parameters (textures and colors) based on the
 * read lines.
 *
 * @param map A pointer to the t_map structure where the scene data will be stored.
 * @param map_fd File descriptor from which the map data is read.
 * @param current_map_row Double pointer to the string that holds the current map row being processed.
 * @return An integer indicating success (SUCCESS) or failure (FAILURE).
 */
static int	map_load_scene(t_map *map, int map_fd, char **current_map_row)
{
	char	*texture_id;

	while (true)
	{
		*current_map_row = map_next_valid_row(map_fd);
		if (!*current_map_row || !ft_is_alpha(*current_map_row[0]))
			break ;
		texture_id = map_get_texture_id(*current_map_row);
		if(!map_set_scene(map, texture_id, *current_map_row))
		{
			free(texture_id);
			return(FAILURE);
		}
		free(texture_id);
	}
	if (!map->EA_texture_fd || !map->SO_texture_fd || !map->WE_texture_fd
		|| !map->EA_texture_fd || !check_colors(map))
	{
		return (FAILURE);
	}
	return (SUCCESS);
}

/* -------------------------------- clean-up -------------------------------- */

/**
 * @brief Closes texture file descriptors if they were opened
 *
 * @param map A pointer to the t_map structure whose file descriptors are to be closed
 */
void	map_close(t_map *map)
{
	if (map->NO_texture_fd)
		close (map->NO_texture_fd);
	if (map->SO_texture_fd)
		close (map->SO_texture_fd);
	if (map->WE_texture_fd)
		close (map->WE_texture_fd);
	if (map->EA_texture_fd)
		close (map->EA_texture_fd);
}

/**
 * @brief Frees all dynamically allocated resources associated with the given t_map structure.
 *
 * @param map A pointer to the t_map structure whose resources are to be freed.
 */
void	map_free(t_map *map)
{
	if (map)
	{
		map_close(map);
		ft_free_double((void **)map->grid);
		free(map);
		map = NULL;
	}
}

/**
 * @brief Checks if the file extension of the given map path is '.cub'.
 *
 * This function verifies that the map file has the '.cub' extension. If not, it prints an extension error message.
 *
 * @param map_path Pointer to the path of the map file.
 * @return true if the file has a '.cub' extension, false otherwise.
 */
bool	map_extension_check(char *map_path)
{
	if (!map_path)
		return (write_error_msg(EXTENSION_ERROR));
	char *extension = ft_strrchr(map_path, '.');
	if (!extension)
		return (write_error_msg(EXTENSION_ERROR));
	if (ft_strncmp(extension, ".cub", 4))
		return (write_error_msg(EXTENSION_ERROR));
	else
		return (true);
}
