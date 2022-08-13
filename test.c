/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:17:49 by rthammat          #+#    #+#             */
/*   Updated: 2022/08/12 23:29:00 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_init(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, 500,500, "mlx 42");
	fdf->tab = NULL;
	fdf->x1 = 0;
	fdf->y1 = 0;
	fdf->x2 = 500;
	fdf->y2 = 500;
	fdf->height = 0;
	fdf->width = 0;
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc <= 1)
	{
		ft_putstr_fd("No file argument included\n", 2);
		exit(1);
	}
	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		exit(1);
	fdf_init(fdf);
	fdf->height = get_height(argv[1]);
	fdf->width = get_width(argv[1]);
	printf("height is %i\n", fdf->height);
	printf("width is %i\n", fdf->width);
	if (fdf->height < 0 || fdf->width < 0)
		exit(-1);
	fdf->tab = create_tab(fdf);
	if (fdf->tab == NULL)
		exit(1);
	int i = 0;
	while (i < fdf->height)
	{
		int j = 0;
		while (j < fdf->width)
		{
			fdf->tab[i][j] = 0;
			++j;
		}
		++i;
	}
	i = 0;
	while (i < fdf->height)
	{
		int j = 0;
		while (j < fdf->width)
		{
			printf("%i", fdf->tab[i][j]);
			printf(" ");
			++j;
		}
		printf("\n");
		++i;
	}
	free_tab(fdf);
	/*draw_line(fdf);
	fdf->x1 = 0;
	fdf->y1 = 500;
	fdf->x2 = 500;
	fdf->y2 = 0;
	draw_line(fdf);
	mlx_loop(fdf->mlx_ptr);*/
	free(fdf);
	return (0);
}
