#include <cub3D.h>

int main()
{
	t_mlx	*mlx_core;

	mlx_core = init_mlx_core();
	mlx_loop_hook(mlx_core->mlx, no_event, mlx_core); // the no event hook, needs to be there idk why, this executes code inside the no event function in case there are no events to handle
	mlx_key_hook(mlx_core->window, key_hook, mlx_core); // the key hook
	//mlx_hook() // hook is for any general event, key_hook for example only handles key-releases, a more general form is mlx_hook
	mlx_loop(mlx_core->mlx); // recieves events
}



