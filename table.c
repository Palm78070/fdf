/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 21:28:47 by rthammat          #+#    #+#             */
/*   Updated: 2022/08/12 23:24:17 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_tab(t_fdf *fdf)
{
	int	i;

	i = -1;
	while (++i < fdf->height)
		free(fdf->tab[i]);
	//free(tab[i]);
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
	int	**res;

	i = -1;
	res = (int **)malloc(fdf->height * sizeof(int *));
	if (!res)
	{
		perror("error");
		return NULL;
	}
	while (++i < fdf->height)
	{
		res[i] = (int *)malloc(fdf->width * sizeof(int));
		if (!res[i])
		{
			clear_tab(res, i);
			perror("error");
			return (NULL);
		}
	}
	return (res);
}

/*int	**create_tab(t_fdf *fdf)
{
	int	i;

	i = -1;
	fdf->tab = (int **)malloc(fdf->height * sizeof(int *));
	if (!fdf->tab)
	{
		perror("error");
		return NULL;
	}
	while (++i < fdf->height)
	{
		fdf->tab[i] = (int *)malloc(fdf->width * sizeof(int));
		if (!fdf->tab[i])
		{
			clear_tab(fdf->tab, i);
			perror("error");
			return (NULL);
		}
	}
	return (fdf->tab);
}*/
