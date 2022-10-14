/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:17:49 by rthammat          #+#    #+#             */
/*   Updated: 2022/10/15 02:38:09 by rath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	dt_init(t_fdf *dt)
{
	dt->mlx_ptr = mlx_init();
	dt->sc_w = 800;
	dt->sc_h = 800;
	dt->win_ptr = mlx_new_window(dt->mlx_ptr, dt->sc_w, dt->sc_h, "fdf");
	/*dt->tab = NULL;
	dt->color = NULL;*/
	dt->c = 0;
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
	dt->zm = 20;
	dt->xsc = dt->zm * cos(0.5236);
	dt->ysc = dt->zm * sin(0.5236);
}

void	free_all(t_fdf *dt)
{
	/*if (dt)
	{
		if (dt->mlx_ptr)
			mlx_destroy_image(dt->mlx, dt->mlx_ptr);
	}*/
	if (dt->tab != NULL)
		free_tab(dt, dt->tab);
	free(dt);
}

void	send_err(t_fdf *dt)
{
	perror("error");
	free_all(dt);
	exit(1);
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
	if (dt->height < 0 || dt->width < 0)
	{
		free_all(dt);
		exit(-1);
	}
	get_tab(dt, argv[1]);
	//dt->tab = create_tab(dt);
	//dt->color = create_tab(dt);
	//fill_color(dt, argv[1]);
	/*int i = 0;
	printf("\n");
	while (i < dt->height)
	{
		int j = -1;
		while (++j < dt->width)
			dt->color[i][j] = 0xFFFFFF;
		++i;
	}*/
	//fill_tab(dt, argv[1]);
	/*int i = 0;
	printf("\n");
	while (i < dt->height)
	{
		int j = -1;
		while (++j < dt->width)
			dt->color[i][j] = 0xFFFFFF;
		++i;
	}*/
	/*int i = 1;
	printf("\n");
	while (i < dt->height)
	{
		int j = -1;
		while (++j < dt->width)
			printf("%7x", dt->color[i][j]);
		printf("\n");
		++i;
	}*/
	/*int i = 0;
	i = 0;
	while (i < dt->height)
	{
		int j = -1;
		while (++j < dt->width)
			printf("%3i", dt->tab[i][j]);
		printf("\n");
		++i;
	}*/
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
	mlx_loop(dt->mlx_ptr);
	//free_all(dt);
	return (0);
}
