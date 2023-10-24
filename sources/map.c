#include "cub3D.h"

static int	__open_map(char *map_path);
static t_map	*__init_map(void);
static int __resize_map(t_map *map);
static int push(char *row, t_map *map);

t_map	*load_map(char *map_path)
{
	t_map	*map;
	int		map_fd;
	char	*map_row;

	map_fd = __open_map(map_path);
	if (map_fd == -1)
	{
		write_error_msg(MAP_FAIL);
		return NULL;
	}
	map = __init_map();
	if (!map)
	{
		write_error_msg(MALLOC_FAIL);
		return NULL;
	}
	while (true)
	{
		map_row = get_next_line(map_fd);
		if (!map_row)
			break ;
		else
			push(map_row, map);
	}
	return map;
}
void	free_map(t_map *map)
{
	ft_free_double((void **)map->grid);
	free(map);
}
static int __resize_map(t_map *map)
{
	char	**old_array;
	int		i;

	old_array = map->grid;
	map->__row_capacity *= 2;
	map->grid = malloc(sizeof(char *) * map->__row_capacity);
	if(!map->grid)
		return(write_error_msg(MALLOC_FAIL));
	while (i < map->n_rows)
	{
		map->grid[i] = old_array[i];
		i++;
	}
	free(old_array);
	return 1;
}
static t_map	*__init_map(void)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		write_error_msg(MALLOC_FAIL);
	map->n_rows = 0;
	map->__row_capacity = MAP_INITIAL_CAPACITY;
	map->grid= ft_calloc(map->__row_capacity, sizeof(char *));
	if (!map->grid)
	{
		write_error_msg(MALLOC_FAIL);
		free (map);
		map = NULL;
	}
	return (map);
}
static int	__open_map(char *map_path)
{
	int	map_fd;

	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		write_error_msg(MAP_FAIL);
	return (map_fd);
}
static int push(char *row, t_map *map)
{
	if (map->n_rows == map->__row_capacity)
	{
		if(!__resize_map(map))
			return -1;
	}
	map->grid[map->n_rows++] = row;
	return 0;
}
