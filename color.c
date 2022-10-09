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

void	fill_color(t_fdf *dt, char *s, int h, int w)
{
	char	*tmp;

	tmp = ft_strchr(s, ',');
	if (tmp == NULL)
		send_err(dt);
	++tmp;
	dt->color[h][w] = convert_hex(tmp);
}
