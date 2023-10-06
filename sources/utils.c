#include <cub3D.h>

/* ------------------------------- error utils ------------------------------ */
int	write_error_msg(char *error_msg)
{
	write(2, error_msg, ft_strlen(error_msg));
	return (0);
}
