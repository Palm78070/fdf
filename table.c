/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 21:28:47 by rthammat          #+#    #+#             */
/*   Updated: 2022/10/15 02:32:11 by rath             ###   ########.fr       */
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

/*int	**create_tab(t_fdf *dt)
{
	int	i;
	int	**res;

	i = -1;
	res = (int **)malloc((dt->height) * sizeof(int *));
	if (!res)
		send_err(dt);
	while (++i < dt->height)
	{
		res[i] = (int *)malloc(dt->width * sizeof(int));
		if (!res[i])
		{
			clear_tab(res, i);
			send_err(dt);
		}
		ft_memset(res[i], 0, sizeof(res[i]));/////////
	}
	return (res);
}*/

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

/*void	insert_num(t_fdf *dt, char *s)
{
	static int	h = 0;
	int	w;
	char	**sp;

	sp = ft_split(s, ' ');
	if (!sp)
	{
		free_all(dt);
		perror("error");
		exit(1);
	}
	w = 0;
	while (sp[w] != NULL)
	{
		dt->tab[h][w] = ft_atoi(sp[w]);
		++w;
	}
	++h;
	free_double(sp);
}*/

/*void	insert_num(t_fdf *dt, char *s, int h)
{
	int	w;
	char	**sp;

	sp = ft_split(s, ' ');
	if (!sp)
		send_err(dt);
	w = -1;
	while (sp[++w] != NULL)
		dt->tab[h][w] = ft_atoi(sp[w]);
	free_double(sp);
}*/

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
		insert_color(dt, sp[w], h, w);
		//dt->tab[h][w].color = 0xFFFFFF;
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
	dt->tab = create_tab(dt);
	while (s != NULL)
	{
		insert_num(dt, s, h++);
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
}
