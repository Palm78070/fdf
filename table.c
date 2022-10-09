/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 21:28:47 by rthammat          #+#    #+#             */
/*   Updated: 2022/10/07 21:06:43 by rath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_tab(t_fdf *dt, int **arr)
{
	int	i;

	i = -1;
	while (++i < dt->height)
		free(arr[i]);
	free(arr);
	arr = NULL;
}

void	clear_tab(int **arr, int i)
{
	while(i >= 0)
	{
		free(arr[i]);
		--i;
	}
	free(arr);
}

int	**create_tab(t_fdf *dt)
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
	}
	return (res);
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

void	insert_num(t_fdf *dt, char *s)
{
	static int	h = 0;
	int	w;
	char	**sp;

	sp = ft_split(s, ' ');
	if (!sp)
		send_err(dt);
	w = 0;
	while (sp[w] != NULL)
	{
		///////////////////////////////
		if (found_c(sp[w], ','))
			fill_color(dt, sp[w], h, w);
		else
			dt->color[h][w] = 0xFFFFFF;
		///////////////////////////////
		dt->tab[h][w] = ft_atoi(sp[w]);
		++w;
	}
	++h;
	free_double(sp);
}

void	fill_tab(t_fdf *dt, char *file)
{
	int	fd;
	char	*s;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		send_err(dt);
	s = get_next_line(fd);
	while (s != NULL)
	{
		insert_num(dt, s);
		free(s);
		s = get_next_line(fd);
	}
	free(s);
	close(fd);
}
