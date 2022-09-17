/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:17:49 by rthammat          #+#    #+#             */
/*   Updated: 2022/09/17 23:37:14 by rath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	dt_init(t_fdf *dt)
{
	dt->mlx_ptr = mlx_init();
	dt->sc_w = 800;
	dt->sc_h = 800;
	dt->win_ptr = mlx_new_window(dt->mlx_ptr, dt->sc_w, dt->sc_h, "fdf");
	dt->tab = NULL;
	dt->x1 = 0;
	dt->y1 = 0;
	dt->dx = 0;
	dt->dy = 0;
	dt->height = 0;
	dt->width = 0;
	dt->zm = 20;
	dt->xsc = dt->zm * cos(0.5236);
	dt->ysc = dt->zm * sin(0.5236);
}

void	free_all(t_fdf *dt)
{
	if (dt->tab)
		free_tab(dt);
	free(dt);
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
	dt_init(dt);
	dt->height = get_height(argv[1]);
	dt->width = get_width(argv[1]);
	printf("height %i\n", dt->height);
	printf("width %i\n", dt->width);
	if (dt->height < 0 || dt->width < 0)
	{
		free_all(dt);
		exit(-1);
	}
	dt->tab = create_tab(dt);
	int i = 0;
	fill_tab(dt, argv[1]);
	i = 0;
	while (i < dt->height)
	{
		int j = -1;
		while (++j < dt->width)
			printf("%3i", dt->tab[i][j]);
		printf("\n");
		++i;
	}
	//draw2(dt);
	/*set_start(dt, dt->sc_w / 2, 400);
	float x_sc = dt->zm * cos(0.5236);
	float y_sc = dt->zm * sin(0.5236);
	line(dt, dt->x1 + x_sc, dt->y1 + y_sc);
	set_start(dt, dt->sc_w / 2, 400);
	line(dt, dt->x1 + x_sc, dt->y1 - y_sc);*/
	draw4(dt);
	/*set_start(dt, 211.961487, 489.999969);
	while (dt->x1 < 229.281982)
	{
		line(dt, dt->x1 + 0.1, dt->y1 - 10);
		set_start(dt, dt->x1 + 1, dt->y1 - 10);
	}*/
	/*set_start(dt, 211.961487, 510.000031);
	while (dt->x1 < 229.281982)
	{
		line(dt, dt->x1 + 0.1, dt->y1 - 11);
		set_start(dt, dt->x1 + 1, dt->y1 - 11);
	}*/
	mlx_loop(dt->mlx_ptr);
	free_all(dt);
	return (0);
}
