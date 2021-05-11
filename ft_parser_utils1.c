/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 19:18:59 by aisraely          #+#    #+#             */
/*   Updated: 2021/05/10 19:19:00 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_getworldmap(char *mappath, t_parsed *res)
{
	int		fd;
	char	*line;
	int		r;
	int		x;

	fd = open(mappath, O_RDONLY);
	ft_setup_map(res, mappath);
	x = 0;
	while (get_next_line(fd, &line))
		if (ft_ismaprow(line))
		{
			ft_writerow(line, res, x++);
			while (1)
			{
				r = get_next_line(fd, &line);
				ft_writerow(line, res, x++);
				if (!r)
					break ;
			}
		}
	if (res->player.posx < 0 || res->player.posy < 0)
		ft_exit("The player is missing.");
	ft_checkwalls(res->map.m, res->map.h, res->map.w);
	free(line);
	close(fd);
}

int		ft_getmapheight(char *mappath)
{
	int		fd;
	char	*line;
	int		height;
	int		r;

	height = 0;
	fd = open(mappath, O_RDONLY);
	while (get_next_line(fd, &line))
		if (ft_ismaprow(line))
		{
			height++;
			while (1)
			{
				r = get_next_line(fd, &line);
				if (!(ft_ismaprow(line)))
					ft_exit("Invalid map row.");
				height++;
				if (!r)
					break ;
			}
		}
	free(line);
	close(fd);
	return (height);
}

int		ft_getmapwidth(char *mappath)
{
	int		fd;
	char	*line;
	int		width;
	int		r;

	width = 0;
	fd = open(mappath, O_RDONLY);
	while (get_next_line(fd, &line))
		if (ft_ismaprow(line))
			while (1)
			{
				r = get_next_line(fd, &line);
				if (!(ft_ismaprow(line)))
					ft_exit("Invalid map row.");
				if (ft_strlen(line) > width)
					width = ft_strlen(line);
				if (!r)
					break ;
			}
	free(line);
	close(fd);
	return (width);
}

int		ft_getsprnum(char *mappath)
{
	int		fd;
	char	*line;
	int		sprnum;
	int		i;

	sprnum = 0;
	fd = open(mappath, O_RDONLY);
	while (get_next_line(fd, &line))
		if (ft_ismaprow(line))
			while (get_next_line(fd, &line))
			{
				i = 0;
				if (!(ft_ismaprow(line)))
					ft_exit("Invalid map row.");
				while (*(line + i))
				{
					if (*(line + i) == '2')
						sprnum++;
					i++;
				}
			}
	free(line);
	close(fd);
	return (sprnum);
}

void	ft_writerow(char *line, t_parsed *res, int x)
{
	int	i;

	i = 0;
	while (*(line + i))
	{
		if (*(line + i) == ' ')
			res->map.m[x][i] = 8;
		else if (*(line + i) == '0' || *(line + i) == '1'
				|| *(line + i) == '2')
		{
			res->map.m[x][i] = *(line + i) - 48;
			if (*(line + i) == '2')
			{
				res->sprites[res->i]->posx = (double)x + 0.5;
				res->sprites[(res->i)++]->posy = (double)i + 0.5;
			}
		}
		else if (*(line + i) == 'N' || *(line + i) == 'W'
				|| *(line + i) == 'E' || *(line + i) == 'S')
			ft_initplayer(res, *(line + i), x, i);
		i++;
	}
	while (i < res->map.w)
		res->map.m[x][i++] = 8;
}
