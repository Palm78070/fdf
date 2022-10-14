#include "fdf.h"

int	convert_hex(char *s)
{
	int	len;
	int	res;
	int	c;
	int	n;

	len = ft_strlen(s) - 1;
	res = 0;
	c = 0;
	n = 0;
	while (len >= 0)
	{
		if (s[len] == 'x' || s[len] == 'X')
			break ;
		if (s[len] >= 'a' && s[len] <= 'f')
			c = (s[len] - 'a') + 10;
		else if (s[len] >= 'A' && s[len] <= 'F')
			c = (s[len] - 'A') + 10;
		else
			c = s[len] - '0';
		res = res + (c * pow(16, n++));
		--len;
	}
	return (res);
}

int	found_c(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (1);
	}
	return (0);
}

/*void	fill_color(t_fdf *dt, char *s, int h, int w)
{
	char	*tmp;

	tmp = ft_strchr(s, ',');
	if (tmp == NULL)
		send_err(dt);
	++tmp;
	dt->color[h][w] = convert_hex(tmp);
}*/

void	insert_color(t_fdf *dt, char *s, int h, int w)
{
	char	*tmp;

	tmp = NULL;
	if (!found_c(s, ','))
	{
		dt->tab[h][w].color = convert_hex("0xFFFFFF");
		return ;
	}
	tmp = ft_strchr(s, ',');
	if (tmp == NULL)
		send_err(dt);
	++tmp;
	dt->tab[h][w].color = convert_hex(tmp);
}

/*void	insert_color(t_fdf *dt, char *s, int h)
{
	int	w;
	char	*tmp;
	char	**sp;

	tmp = NULL;
	sp = ft_split(s, ' ');
	if (!sp)
		send_err(dt);
	w = 0;
	while (sp[w] != NULL)
	{
		if (found_c(sp[w], ','))
		{
			tmp = ft_strchr(sp[w], ',');
			if (tmp++ == NULL)
				send_err(dt);
			//++tmp;
			dt->color[h][w] = convert_hex(tmp);
		}
		else
			dt->color[h][w] = 0xFFFFFF;
		++w;
	}
	free_double(sp);
}*/

/*void	fill_color(t_fdf *dt, char *file)
{
	int	fd;
	int	h;
	char	*s;

	fd = open(file, O_RDONLY);
	h = 0;
	if (fd < 0)
		send_err(dt);
	s = get_next_line(fd);
	while (s != NULL)
	{
		insert_color(dt, s, h++);
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
}*/
