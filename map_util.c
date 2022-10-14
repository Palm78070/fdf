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
		s2 = ft_split(s, ' ');
		while (s2[count])
			++count;
		free_double(s2);
	}
	while (s != NULL)
	{
		free(s);
		s = get_next_line(fd);
	}
	if (close(fd) == -1)
		perror("error");
	return (count);
}

void	get_map_size(t_fdf *dt, char *input)
{
	dt->height = get_height(input);
	dt->width = get_width(input);
}

void	set_start(t_fdf *dt, float x, float y)
{
	dt->x1 = x;
	dt->y1 = y;
}
