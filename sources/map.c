#include "cub3D.h"

/* -------------------------------------------------------------------------- */
/*                                    BUGS                                    */
/* -------------------------------------------------------------------------- */

/* ----------------------------- initialization ----------------------------- */
static t_map	*map_init(void);
/* ---------------------------------- grid ---------------------------------- */
static int		map_resize(t_map *map);
static int		map_add_row(char *row, t_map *map);
static int		map_load_grid(t_map *map, int map_fd, char **current_map_row);
/* ---------------------------------- scene --------------------------------- */
static bool		map_row_is_empty(char *current_map_row);
static char		*map_next_valid_row(int map_fd);
static char		*map_get_texture_id(char *current_map_row);
static void		map_set_texture(int	*texture_fd, char *current_map_row);
static void		map_set_color(int *map_color, char *current_map_row);
static int		map_load_scene(t_map *map, int map_fd, char **current_map_row);

/* -------------------------------- utilities ------------------------------- */

static void		map_close(t_map *map);
static int		verifiy_open(char *map_path, int options);
static void		empty_gnl(char *current_map_row, int map_fd);

/* -------------------------------------------------------------------------- */
/*                                  Load Map                                  */
/* -------------------------------------------------------------------------- */
static void empty_gnl(char *current_map_row, int map_fd)
{
	while (true)
	{
		if (!current_map_row)
			break;
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

	map_fd = verifiy_open(map_path, O_RDONLY);
	if (map_fd == FAILURE)
		return (NULL);
	map = map_init();
	if (!map)
		return (NULL);
	if (!map_load_scene(map, map_fd, &current_map_row))
	{
		empty_gnl(current_map_row, map_fd);
		map_free(map);
		return (NULL);
	}
	if (!map_load_grid(map, map_fd, &current_map_row))
	{
		empty_gnl(current_map_row, map_fd);
		map_free(map);
		return (NULL);
	}
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
static int	verifiy_open(char *file_path, int options)
{
	int	fd;

	fd = open(file_path, options);
	if (fd == -1)
	{
		write_error_msg(OPEN_FAIL);
		write(2, file_path, ft_strlen(file_path));
		write(2, "\n", 1);
		return (FAILURE);
	}
	return (fd);
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
	map->n_rows = 0;
	map->NO_texture_fd = 0;
	map->SO_texture_fd = 0;
	map->WE_texture_fd = 0;
	map->EA_texture_fd = 0;
	map->grid_capacity = MAP_INITIAL_CAPACITY;
	map->grid= ft_calloc(map->grid_capacity, sizeof(char *));
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
static	int map_load_grid(t_map *map, int map_fd, char **current_map_row)
{
	while (*current_map_row)
	{
		if(!map_add_row(*current_map_row, map))
			return (FAILURE);
		*current_map_row = get_next_line(map_fd);
	}
	// if (map_is_enclosed(map, map->x, map->y));
	if (map_is_enclosed(map, 1, 1)) // only for debugging
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
	map->grid = ft_calloc(sizeof(char *),  map->grid_capacity);
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

static char	*map_get_texture_id(char *current_map_row)
{
	int	id_length;

	id_length = 0;
	while (current_map_row && current_map_row[id_length] != ' ')
		id_length++;
	if (id_length != 2 && id_length != 1)
		return (NULL);
	return (ft_substr(current_map_row, 0, id_length));
}

static void	map_set_texture(int	*texture_fd, char *current_map_row)
{
	char	*texture_path;

	texture_path= ft_substr(current_map_row, 3, ft_strlen(current_map_row) - 3);
	*texture_fd = verifiy_open(texture_path, O_RDONLY);
	free(current_map_row);
	free(texture_path);
	if (*texture_fd == FAILURE)
		write_error_msg(SCENE_FAIL);
}

static void	map_set_color(int *map_color, char *current_map_row)
{
	// get color string
	char	*color_string;
	char	**rgb_color_strings;
	int		i;

	color_string = ft_substr(current_map_row, 2, ft_strlen(current_map_row) - 2); // in the format x[x*],x[x*],x[x*]
	rgb_color_strings = ft_split(color_string, ',');
	i = 0;
	while (i < TOTAL_COLORS)
	{
		map_color[i] = ft_atoi(rgb_color_strings[i]);
		if (map_color[i] > 255 || map_color[i] < 0)
		{
			write_error_msg(SCENE_FAIL);
			map_color = FAILURE;
		}
		i++;
	}
	ft_free_double((void **)rgb_color_strings);
	free(color_string);
	free(current_map_row);
}

static int	map_set_scene(t_map *map, char *texture_id, char *current_map_row)
{
	if (!texture_id)
		return (FAILURE);
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
		return (FAILURE);
	return (SUCCESS);
}
static int	map_load_scene(t_map *map, int map_fd, char **current_map_row)
{
	char	*texture_id;

	while (true)
	{
		*current_map_row = map_next_valid_row(map_fd);
		if (!*current_map_row || !ft_is_alpha(*current_map_row[0]))
			break ;
		texture_id = map_get_texture_id(*current_map_row);
		map_set_scene(map, texture_id, *current_map_row);
		free(texture_id);
	}
	if (!map->EA_texture_fd || !map->SO_texture_fd || !map->WE_texture_fd
		|| !map->EA_texture_fd || !map->f_color || !map->c_color)
	{
		map_close(map);
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
		close (map->EA_texture_fd);
	if (map->SO_texture_fd)
		close (map->EA_texture_fd);
	if (map->WE_texture_fd)
		close (map->EA_texture_fd);
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
		ft_free_double((void **)map->grid);
		free(map);
		map = NULL;
	}
}
