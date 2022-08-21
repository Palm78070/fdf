/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 21:28:47 by rthammat          #+#    #+#             */
/*   Updated: 2022/08/21 21:36:53 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_tab(t_fdf *dt)
{
	int	i;

	i = -1;
	while (++i < dt->height)
		free(dt->tab[i]);
	free(dt->tab);
	dt->tab = NULL;
}

void	clear_tab(int **tab, int i)
{
	while(i >= 0)
	{
		free(tab[i]);
		--i;
	}
	free(tab);
}

int	**create_tab(t_fdf *dt)
{
	int	i;

	i = -1;
	dt->tab = (int **)malloc((dt->height) * sizeof(int *));
	if (!dt->tab)
	{
		perror("error");
		free_all(dt);
		exit(1);
	}
	while (++i < dt->height)
	{
		dt->tab[i] = (int *)malloc(dt->width * sizeof(int));
		if (!dt->tab[i])
		{
			clear_tab(dt->tab, i);
			perror("error");
			free_all(dt);
			exit(1);
		}
	}
	return (dt->tab);
}

void	insert_num(t_fdf *dt, char *s)
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
}

void	fill_tab(t_fdf *dt, char *file)
{
	int	fd;
	char	*s;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("error");
		free_all(dt);
		exit(1);
	}
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
