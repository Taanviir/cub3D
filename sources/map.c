#include "cub3D.h"

static int		map_open(char *map_path);
static t_map	*map_init(void);
static int		map_resize(t_map *map);
static int		map_add_row(char *row, t_map *map);
static int		map_load_grid(t_map *map, int map_fd);

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
	int		map_fd;

	map_fd = map_open(map_path);
	map = map_init();
	if (!map_fd || !map)
		return (NULL);
	if (!map_load_grid(map, map_fd))
		return (NULL);
	return map;
}
/**
 * @brief Reads the grid data from the map file descriptor and populates the t_map structure.
 *
 * @param map A pointer to the t_map structure to populate.
 * @param map_fd The file descriptor of the map to read from.
 *
 * @return SUCCESS if the grid is read and populated successfully, FAILURE otherwise.
 */
static	int map_load_grid(t_map *map, int map_fd)
{
	char	*current_map_row;

	while (true)
	{
		current_map_row = get_next_line(map_fd);
		if (!current_map_row)
			break ;
		else
		{
			if(!map_add_row(current_map_row, map))
				return (FAILURE);
		}
	}
	return (SUCCESS);
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

/**
 * @brief Opens the map file at the given path for reading.
 *
 * @param map_path The file path of the map to open.
 *
 * @return The file descriptor for the opened map file, or 0 if the file cannot be opened.
 */
static int	map_open(char *map_path)
{
	int	map_fd;

	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
	{
		write_error_msg(MAP_FAIL);
		return (FAILURE);
	}
	return (map_fd);
}

/**
 * @brief Adds a row to the grid array in the t_map structure.
 *
 * Resizes the grid array if its current capacity is reached before adding the row.
 *
 * @param row The row data to add.
 * @param map A pointer to the t_map structure that holds the grid to be modified.
 *
 * @return SUCCESS if the row is successfully added, FAILURE otherwise (e.g., resizing failure).
 */
static int map_add_row(char *row, t_map *map)
{
	if (!row)
		return (FAILURE);
	if (map->n_rows == map->grid_capacity)
	{
		if(!map_resize(map))
			return (FAILURE);
	}
	map->grid[map->n_rows++] = row;
	return (SUCCESS);
}
