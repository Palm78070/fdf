/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:17:49 by rthammat          #+#    #+#             */
/*   Updated: 2022/10/23 00:05:42 by rath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	dt_init(t_fdf *dt)
{
	dt->mlx_ptr = NULL;
	dt->sc_w = 800;
	dt->sc_h = 800;
	dt->win_ptr = NULL;
	dt->c = 0;
	dt->tab = NULL;
	dt->x1 = 0;
	dt->y1 = 0;
	dt->x2 = 0;
	dt->y2 = 0;
	dt->z = 0;
	dt->zx = 0;
	dt->zy = 0;
	dt->dx = 0;
	dt->dy = 0;
	dt->height = 0;
	dt->width = 0;
	dt->zm = 20;
	dt->xsc = dt->zm * cos(0.5236);
	dt->ysc = dt->zm * sin(0.5236);
}

void	ft_pixel_put(t_fdf *dt, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= dt->sc_w || y < 0 || y >= dt->sc_h)
		return ;
	dst = dt->img.addr + (y * dt->img.size_line) + (x * (dt->img.bpp / 8));
	*(unsigned int *)dst = color;
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
	printf("target color %i\n", 0xFF0000);	
	draw4(dt);
	/*i = 0;
	printf("\n");
	while (i < dt->height)
	{
		int j = -1;
		while (++j < dt->width)
			printf("%7x", dt->color[i][j]);
		printf("\n");
		++i;
	}*/
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img.ptr, 0, 0);
	//mlx_loop_hook(dt->mlx_ptr, draw4, dt);
	mlx_hook(dt->win_ptr, 2, 1L << 0, &handle_key, dt);
	mlx_hook(dt->win_ptr, 17, 0L, &handle_cross, dt);
	mlx_loop(dt->mlx_ptr);
	//free_all(dt);
	return (0);
}
