/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 21:37:13 by rthammat          #+#    #+#             */
/*   Updated: 2022/09/21 23:13:24 by rath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_height(char *file)
{
	int	fd;
	int	count;
	char	*s;

	fd = open(file, O_RDONLY);
	count = 0;
	if (fd < 0)
	{
		perror("error");
		return (-1);
	}
	s = get_next_line(fd);
	while (s != NULL)
	{
		++count;
		free(s);
		s = get_next_line(fd);
	}
	free(s);
	if (close(fd) == -1)
		perror("error");
	return (count);
}

int	get_width(char *file)
{
	int	fd;
	int	count;
	char	*s;
	char	**s2;

	fd = open(file, O_RDONLY);
	count = 0;
	if (fd < 0)
	{
		perror("error");
		return (-1);
	}
	s = get_next_line(fd);
	if (s != NULL)
	{
		int i = -1;
		s2 = ft_split(s, ' ');
		while (s2[++i])
			++count;
		free_double(s2);
	}
	while (s != NULL)
		s = get_next_line(fd);
	free(s);
	if (close(fd) == -1)
		perror("error");
	return (count);
}

void	set_start(t_fdf *dt, float x, float y)
{
	dt->x1 = x;
	dt->y1 = y;
}

void	check_draw(t_fdf *dt, int h, int w)
{
	if (dt->tab[h][w] != 0)
	{
		dt->z = (dt->tab[h][w] / 10) * 190;
		set_start(dt, dt->x1, dt->y1 - dt->z);
		if (dt->tab[h][w + 1] != 0)
			line(dt, dt->x1 + dt->xsc, dt->y1 - dt->ysc);
		if (dt->tab[h + 1][w] != 0)
			line(dt, dt->x1 + dt->xsc, dt->y1 + dt->ysc);
		set_start(dt, dt->x1, dt->y1 + dt->z);
	}
	if (dt->tab[h][w] == 0)
	{
		if (dt->tab[h + 1][w] == 0)
			line(dt, dt->x1 + dt->xsc, dt->y1 + dt->ysc);
		if (dt->tab[h][w + 1] == 0)
			line(dt, dt->x1 + dt->xsc, dt->y1 - dt->ysc);
		z_spot(dt, h, w);
	}
	set_start(dt, dt->x1 + dt->xsc, dt->y1 - dt->ysc);
}

void	draw4(t_fdf *dt)
{
	int	w;
	int	h;
	float	x2;
	float	y2;

	h = -1;
	x2 = (dt->sc_w / 5);
	y2 = dt->sc_h / 2 + 100;
	set_start(dt, dt->sc_w / 5, dt->sc_h / 2 + 100);
	while (++h < dt->height - 1)
	{
		w = -1;
		while (++w < dt->width - 1)
			check_draw(dt, h, w);
		set_start(dt, dt->x1, dt->y1 - 1); //////////////close
		line(dt, dt->x1 + dt->xsc, dt->y1 + dt->ysc); /////////close
		y2 += dt->ysc;
		x2 += dt->xsc;
		set_start(dt, x2, y2);
	}
	w = -1;
	while (++w < dt->width - 1)
	{
		line(dt, dt->x1 + dt->xsc, dt->y1 - dt->ysc);
		set_start(dt, dt->x1 + dt->xsc, dt->y1 - dt->ysc);
	}
}
