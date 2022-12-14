/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 21:01:01 by rthammat          #+#    #+#             */
/*   Updated: 2022/12/14 21:35:16 by rath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	check_color_format(char *s)
{
	int	i;

	i = -1;
	if (s[0] != '0' && s[1] != 'x' && ft_strlen(s) != 8)
		return (0);
	i = 1;
	while (s[++i] && s[i] != '\n')
	{
		if (!ft_isdigit(s[i]) && !(ft_isalpha(s[i])))
			return (0);
	}
	if (i == 0 || i > 8)
		return (0);
	return (1);
}

static int	char_ok(char *s)
{
	if (s[1] != ' ' && s[1] != ',' && s[1] != '\n' && s[1] != '\0')
		return (0);
	return (1);
}

int	check_str_input(char *s)
{
	int	i;

	i = -1;
	if (s[0] == '0' && !char_ok(s))
		return (0);
	if (s[0] == '-')
		i = 1;
	while (s[++i] && s[i] != '\n')
	{
		if (!ft_isdigit(s[i]) && s[i] != ' ' && s[i] != ',')
			return (0);
		if (s[i] == ',')
		{
			if (!check_color_format(&s[i + 1]))
				return (0);
			else
				return (1);
		}
	}
	return (1);
}

int	filename_ok(char *s)
{
	int	len;

	len = ft_strlen(s) - 4;
	if (s[len] != '.')
		return (0);
	if (s[len + 1] != 'f')
		return (0);
	if (s[len + 2] != 'd')
		return (0);
	if (s[len + 3] != 'f')
		return (0);
	return (1);
}
