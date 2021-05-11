/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 22:00:49 by aisraely          #+#    #+#             */
/*   Updated: 2021/05/09 22:00:54 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_check_extension(char *path, char *ext)
{
	int	pathlen;
	int	extlen;

	pathlen = ft_strlen(path);
	extlen = ft_strlen(ext);
	if (!(extlen == 4) || !(pathlen > 4))
		return (0);
	return (*(path + pathlen - 1) == *(ext + extlen - 1)
			&& *(path + pathlen - 2) == *(ext + extlen - 2)
			&& *(path + pathlen - 3) == *(ext + extlen - 3)
			&& *(path + pathlen - 4) == *(ext + extlen - 4));
}

int			ft_ismaprow(char *str)
{
	if (!str || *str == '\0')
		return (0);
	while (*str)
	{
		if (!(*str == ' ' || ft_isdigit(*str) ||
			*str == 'N' || *str == 'S' || *str == 'W' ||
			*str == 'E'))
			return (0);
		str++;
	}
	return (1);
}

static void	ft_checksides(int **map, int height, int width, int j)
{
	int	x;

	while (j < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[j][x] == 1)
				break ;
			if (map[j][x] == 0 || map[j][x] == 2 || x == width - 1)
				ft_exit("The map is not closed from left.");
			x++;
		}
		x = width - 1;
		while (x >= 0)
		{
			if (map[j][x] == 1)
				break ;
			if (map[j][x] == 0 || map[j][x] == 2 || x == 0)
				ft_exit("The map is not closed from right.");
			x--;
		}
		j++;
	}
}

static void	ft_checkabovebelow(int **map, int height, int width, int j)
{
	int	x;

	while (j < width)
	{
		x = 0;
		while (x < height)
		{
			if (map[x][j] == 1)
				break ;
			if (map[x][j] == 0 || map[x][j] == 2 || x == height - 1)
				ft_exit("The map is not closed from above.");
			x++;
		}
		x = height - 1;
		while (x >= 0)
		{
			if (map[x][j] == 1)
				break ;
			if (map[x][j] == 0 || map[x][j] == 2 || x == height - 1)
				ft_exit("The map is not closed from below.");
			x--;
		}
		j++;
	}
}

void		ft_checkwalls(int **map, int height, int width)
{
	ft_checkabovebelow(map, height, width, 0);
	ft_checksides(map, height, width, 0);
}
