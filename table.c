/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 21:28:47 by rthammat          #+#    #+#             */
/*   Updated: 2022/10/28 17:29:27 by rath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_tab(t_fdf *dt, t_tab **arr)
{
	int	i;

	i = -1;
	while (++i < dt->height)
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;
}

void	clear_tab(t_tab **arr, int i)
{
	while(i >= 0)
	{
		free(arr[i]);
		--i;
	}
	free(arr);
}

t_tab	**create_tab(t_fdf *dt)
{
	int	i;

	i = -1;
	dt->tab = (t_tab **)malloc((dt->height) * sizeof(t_tab *));
	if (!dt->tab)
		send_err(dt);
	while (++i < dt->height)
	{
		dt->tab[i] = (t_tab *)malloc(dt->width * sizeof(t_tab));
		if (!dt->tab[i])
		{
			clear_tab(dt->tab, i);
			send_err(dt);
		}
		ft_memset(dt->tab[i], 0, sizeof(t_tab[i]));/////////
	}
	return (dt->tab);
}

void	set_zm(t_fdf *dt, int h, int z)
{
	float	edge;
	float	y_pos;

	edge = 0.3;
	dt->ysc = dt->zm * sin(0.5236);
	y_pos = dt->y_start - (h * dt->ysc) - (z * dt->zm);
	while (fabsf(y_pos - dt->y_start) > (dt->sc_h * edge))
	{
		dt->zm -= 0.1;
		dt->ysc = dt->zm * sin(0.5236);
		y_pos = dt->y_start - (h * dt->ysc) - (z * dt->zm);
	}
	//dt->ysc = dt->zm * sin(0.5236);
	//dt->xsc = dt->zm * cos(0.5236);
	set_projection(dt);
}

void	insert_num(t_fdf *dt, char *s, int h)
{
	int	w;
	char	**sp;

	sp = ft_split(s, ' ');
	if (!sp)
		send_err(dt);
	w = -1;
	while (sp[++w] != NULL)
	{
		dt->tab[h][w].z = ft_atoi(sp[w]);
		set_zm(dt, h, dt->tab[h][w].z);
		insert_color(dt, sp[w], h, w);
	}
	free_double(sp);
}

void	get_tab(t_fdf *dt, char *file)
{
	int	fd;
	int	h;
	char	*s;

	fd = open(file, O_RDONLY);
	h = 0;
	if (fd < 0)
		send_err(dt);
	s = get_next_line(fd);
	//dt->x_start = dt->sc_w * 0.25;
	//dt->x_start = dt->sc_w * 0.1875;
	dt->x_start = dt->sc_w * 0.25;
	dt->y_start = dt->sc_h / 2;
	//dt->y_start = dt->sc_h / 2 + 30;
	dt->tab = create_tab(dt);
	while (s != NULL)
	{
		insert_num(dt, s, h++);
		free(s);
		s = get_next_line(fd);
	}
	//while (find_x_edge(dt) > (dt->sc_w * 0.75))
	//while (find_x_edge(dt) > (dt->sc_w * 0.8125))
	//while (find_x_edge(dt) > (dt->sc_w * 0.75))
	while (find_x_edge(dt) > (dt->sc_w))
		dt->zm -= 0.1;	
	/*if (dt->zm > 0 && (dt->height >= 500 || dt->width >= 500))
		dt->zm = ceil(dt->zm) - 0.5;
	else
		dt->zm = ceil(dt->zm) - 0.1;*/
	//printf("x_last %f\n", dt->x1);
	//dt->zm = 5;
	set_projection(dt);
	mv_middle(dt, dt->x1);
	close(fd);
}
