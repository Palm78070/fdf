/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 21:28:47 by rthammat          #+#    #+#             */
/*   Updated: 2022/08/14 00:21:56 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_tab(t_fdf *fdf)
{
	int	i;

	i = -1;
	while (++i < fdf->height)
		free(fdf->tab[i]);
	free(fdf->tab);
	fdf->tab = NULL;
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

int	**create_tab(t_fdf *fdf)
{
	int	i;

	i = -1;
	fdf->tab = (int **)malloc((fdf->height) * sizeof(int *));
	if (!fdf->tab)
	{
		perror("error");
		free_all(fdf);
		exit(1);
	}
	while (++i < fdf->height)
	{
		fdf->tab[i] = (int *)malloc(fdf->width * sizeof(int));
		if (!fdf->tab[i])
		{
			clear_tab(fdf->tab, i);
			perror("error");
			free_all(fdf);
			exit(1);
		}
	}
	return (fdf->tab);
}

void	insert_num(t_fdf *fdf, char *s)
{
	static int	h = 0;
	int	w;
	char	**sp;

	sp = ft_split(s, ' ');
	if (!sp)
	{
		free_all(fdf);
		perror("error");
		exit(1);
	}
	w = 0;
	while (sp[w] != NULL)
	{
		fdf->tab[h][w] = ft_atoi(sp[w]);
		++w;
	}
	++h;
	free_double(sp);
}

void	fill_tab(t_fdf *fdf, char *file)
{
	int	fd;
	char	*s;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("error");
		free_all(fdf);
		exit(1);
	}
	s = get_next_line(fd);
	while (s != NULL)
	{
		insert_num(fdf, s);
		free(s);
		s = get_next_line(fd);
	}
	free(s);
	close(fd);
}
