#include "fdf.h"

int	handle_key(int key_code, t_fdf *dt)
{
	if (key_code == 53)
		ft_close(dt, "Escape key is pressed, window is closed\n", 1);
	return (0);
}

int	handle_cross(t_fdf *dt)
{
	ft_close(dt, "Cross is pressed, window is closed\n", 1);
	return (0);
}
