#include <cub3D.h>

/* ------------------------------ initializing ------------------------------ */
t_mlx	*init_mlx_core()
{
	t_mlx	*mlx_core;

	mlx_core = malloc(sizeof(t_mlx));
	if (!mlx_core && write_error_msg(MALLOC_FAIL))
		return (NULL);
	mlx_core->mlx = mlx_init();
	if (!mlx_core->mlx && write_error_msg(MLX_INIT_FAIL))
		return (NULL);
	mlx_core->window = mlx_new_window(mlx_core->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!mlx_core->window && write_error_msg(MLX_WIN_FAIL))
		return (NULL);
	return (mlx_core);
}

/* --------------------------------- events --------------------------------- */

int	close_mlx(int keycode, t_mlx *mlx_core)
{
	mlx_destroy_window(mlx_core->mlx, mlx_core->window);
	free(mlx_core);
	return (0);
}
