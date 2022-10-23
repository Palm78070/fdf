/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:17:49 by rthammat          #+#    #+#             */
/*   Updated: 2022/10/23 20:57:13 by rath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	dt_init(t_fdf *dt)
{
	dt->mlx_ptr = NULL;
	dt->sc_w = 800;
	dt->sc_h = 800;
	dt->win_ptr = NULL;
	dt->tab = NULL;
	dt->x1 = 0;
	dt->y1 = 0;
	dt->z = 0;
	dt->zx = 0;
	dt->zy = 0;
	dt->dx = 0;
	dt->dy = 0;
	dt->height = 0;
	dt->width = 0;
	dt->zm = 0;
	dt->xsc = 0;
	dt->ysc = 0;
}

int	check_hw_range(t_fdf *dt, int min, int max)
{
	int	h;
	int	w;

	h = dt->height;
	w = dt->width;
	if ((h >= min && h <= max) && (w >= min && w <= max))
		return (1);
	return (0);
}

float	get_image_size(t_fdf *dt)
{
	float	res;

	if (check_hw_range(dt, 1, 9))
		res = 200;
	if (check_hw_range(dt, 10, 19))
		res = 20;
	if (check_hw_range(dt, 20, 49))
		res = 10;
	if (check_hw_range(dt, 50, 69))
		res = 5;
	dt->xsc = res * cos(0.5236);
	dt->ysc = res * sin(0.5236);
	return (res);
}

int	main(int argc, char **argv)
{
	t_fdf	*dt;

	if (argc <= 1)
	{
		ft_putstr_fd("No file argument included\n", 2);
		exit(1);
	}
	dt = (t_fdf *)malloc(sizeof(t_fdf));
	if (!dt)
		exit(1);
	ft_memset(dt, 0, sizeof(dt));
	dt_init(dt);
	get_map_size(dt, argv[1]);
	printf("height %i\n", dt->height);
	printf("width %i\n", dt->width);
	dt->zm = get_image_size(dt);
	get_tab(dt, argv[1]);
	dt->mlx_ptr = mlx_init();
	if (!dt->mlx_ptr)
		send_err(dt);
	dt->win_ptr = mlx_new_window(dt->mlx_ptr, dt->sc_w, dt->sc_h, "fdf");
	if (!dt->win_ptr)
		send_err(dt);
	dt->img.ptr = mlx_new_image(dt->mlx_ptr, dt->sc_w, dt->sc_h);
	dt->img.addr = mlx_get_data_addr(dt->img.ptr, &dt->img.bpp,
			&dt->img.size_line, &dt->img.endian);
	draw(dt);
	int i = 0;
	printf("\n");
	while (i < dt->height)
	{
		int j = -1;
		while (++j < dt->width)
			printf("%3i", dt->tab[i][j].z);
		printf("\n");
		++i;
	}
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img.ptr, 0, 0);
	mlx_hook(dt->win_ptr, 2, 1L << 0, &handle_key, dt);
	mlx_hook(dt->win_ptr, 17, 0L, &handle_cross, dt);
	mlx_loop(dt->mlx_ptr);
	//free_all(dt);
	return (0);
}
