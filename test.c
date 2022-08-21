/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:17:49 by rthammat          #+#    #+#             */
/*   Updated: 2022/08/21 19:45:07 by rthammat         ###   ########.fr       */
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
	dt->height = 0;
	dt->width = 0;
	dt->zm = 0;
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
	float	r;

	if (argc <= 1)
	{
		ft_putstr_fd("No file argument included\n", 2);
		exit(1);
	}
	r = 0.5236;
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
	/*while (i < fdf->height)
	{
		int j = 0;
		while (j < fdf->width)
		{
			fdf->tab[i][j] = 0;
			++j;
		}
		++i;
	}*/
	fill_tab(dt, argv[1]);
	i = 0;
	while (i < dt->height)
	{
		int j = 0;
		while (j < dt->width)
		{
			printf("%3i", dt->tab[i][j]);
			//printf(" ");
			++j;
		}
		printf("\n");
		++i;
	}
	//dt->zm = 20;
	//draw(dt);
	//set_start(dt, 400, 0);
	//line(dt, 800, 400 / sqrt(3));
	//line(dt, 800, 400 * tan(0.5236));
	//set_start(dt, 400, 0);
	//line(dt, 0, 400 / sqrt(3));
	//line(dt, 0, 400 * tan(0.5236));
	/*set_start(dt, 0, 0);
	line(dt, 800, 800);
	set_start(dt, 800, 0);
	line(dt, 0, 800);
	set_start(dt, 400, 0);
	line(dt, 400, 800);
	set_start(dt, 800, 400);
	line(dt, 0, 400);*/
	//int	start = dt->sc_w / (2 * dt->zm) - (dt->width / 2);
	set_start(dt, 400, 0);
	//int width = dt->width + dt->x1;
	int w = 0;
	int h = -1;
	float x2 = 400 + 20;
	float y2 = 20 * tan(r);
	while (++h < dt->height - 1)
	{
		w = -1;
		while (++w < dt->width - 1)
		{
			line(dt, dt->x1 - 20, dt->y1 + 20 * tan(r));
			line(dt, dt->x1 + 20, dt->y1 + 20 * tan(r));
			set_start(dt, dt->x1 - 20, dt->y1 + 20 * tan(r));
		}
		set_start(dt, x2, y2);
		y2 += (20 * tan(r));
		x2 += 20;
	}	
	printf("h %i\n", h);
	mlx_loop(dt->mlx_ptr);
	free_all(dt);
	return (0);
}
