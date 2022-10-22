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
	if (s[len] == '\n')
		--len;
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

int	find_gap(t_fdf *dt, float x, float y)
{
	if (fabsf(dt->x2 - dt->x1) > fabsf(dt->y2 - dt->y1))
		return (fabsf(x - dt->x1));
	else
		return (fabsf(y - dt->y1));
}

int	ft_blend_color(t_fdf *dt, float x, float y)
{
	float	dr;
	float	dg;
	float	db;
	t_color	c;

	c.r1 = (dt->color.c1 >> 16) & 0xFF;
	c.g1 = (dt->color.c1 >> 8) & 0xFF;
	c.b1 = dt->color.c1 & 0xFF;
	c.r2 = (dt->color.c2 >> 16) & 0xFF;
	c.g2 = (dt->color.c2 >> 8) & 0xFF;
	c.b2 = dt->color.c2 & 0xFF;
	c.line_gap = fmaxf(fabsf(dt->x2 - dt->x1), fabsf(dt->y2 - dt->y1));
	c.gap = find_gap(dt, x, y);
	if (c.gap > c.line_gap)
		c.gap = c.line_gap;
	c.gap_ratio = (c.gap / c.line_gap);
	/*printf("c.gap %f\n", c.gap);
	printf("c.line_gap %f\n", c.line_gap);
	printf("c.gap_ratio %f\n", c.gap_ratio);*/
	/*dr = (dt->color.c1 >> 16 & 0xFF) + ((c.r2 - c.r1) * c.gap_ratio);
	dg = (dt->color.c1 >> 8 & 0xFF) + ((c.g2 - c.g1) * c.gap_ratio);
	db = (dt->color.c1 & 0xFF) + ((c.b2 - c.b1) * c.gap_ratio);*/
	dr = c.r1 + ((c.r2 - c.r1) * c.gap_ratio);
	dg = c.g1 + ((c.g2 - c.g1) * c.gap_ratio);
	db = c.b1 + ((c.b2 - c.b1) * c.gap_ratio);
	/*printf("c.r2 - c.r1 * ratio %f\n", (c.r2 - c.r1) * c.gap_ratio);
	printf("c.g2 - c.g1 * ratio %f\n", (c.g2 - c.g1) * c.gap_ratio);
	printf("c.b2 - c.b1 * ratio %f\n", (c.b2 - c.b1) * c.gap_ratio);
	printf("\n");*/
	return (((int)dr << 16) | ((int)dg << 8) | (int)db);
}
