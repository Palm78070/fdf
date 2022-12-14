/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 21:28:47 by rthammat          #+#    #+#             */
/*   Updated: 2022/12/14 21:13:39 by rthammat         ###   ########.fr       */
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

static void	clear_tab(t_tab **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		--i;
	}
	free(arr);
}

static t_tab	**create_tab(t_fdf *dt)
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
		ft_memset(dt->tab[i], 0, sizeof(t_tab) * dt->width);
	}
	return (dt->tab);
}

static void	insert_num(t_fdf *dt, char *s, int h)
{
	int		w;
	char	**sp;
	int		input_ok;

	sp = ft_split(s, ' ');
	input_ok = 1;
	if (!sp)
		send_err(dt);
	w = -1;
	while (sp[++w] != NULL)
	{
		input_ok = check_str_input(sp[w]);
		if (!input_ok)
			break ;
		dt->tab[h][w].z = ft_atoi(sp[w]);
		insert_color(dt, sp[w], h, w);
	}
	if (w == 1 || !input_ok)
	{
		ft_putstr_fd("Map has incorrect format\n", 2);
		free_all(dt);
		exit(1);
	}
	free_double(sp);
}

void	get_tab(t_fdf *dt, char *file)
{
	int		fd;
	int		h;
	char	*s;

	fd = open(file, O_RDONLY);
	h = 0;
	if (fd < 0)
		send_err(dt);
	s = get_next_line(fd);
	dt->x_start = dt->sc_w * 0.25;
	dt->y_start = dt->sc_h / 2 + 50;
	dt->tab = create_tab(dt);
	while (s != NULL)
	{
		insert_num(dt, s, h++);
		free(s);
		s = get_next_line(fd);
	}
	while (!find_x_edge(dt))
		dt->zm -= 0.1;
	set_projection(dt);
	mv_middle(dt, dt->x1);
	close(fd);
}
