/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 21:18:29 by aisraely          #+#    #+#             */
/*   Updated: 2021/05/10 21:22:43 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_getresolution(t_parsed *res, char *line)
{
	int	nativeh;
	int	nativew;

	mlx_get_screen_size(res->scr.mlx, &nativew, &nativeh);
	if (ft_strchr(line, 'R') && *(ft_strchr(line, 'R') + 1) == ' ')
	{
		if (res->w >= 0 || res->h >= 0)
			ft_exit("Double declaration of resolution.");
		if (ft_fetchdigit(line))
			line = ft_fetchdigit(line);
		else
			ft_exit("Resolution identifier is not followed by numbers.");
		res->w = ft_atoi(line);
		while (ft_isdigit(*line))
			line++;
		if (ft_fetchdigit(line))
			res->h = ft_atoi(ft_fetchdigit(line));
		else
			ft_exit("The height of screen is not specified.");
		if (res->w > nativew)
			res->w = nativew;
		if (res->h > nativeh)
			res->h = nativeh;
	}
}

void	ft_gettexture1(t_parsed *res, char *line)
{
	if (ft_strchr(line, 'N') && *(ft_strchr(line, 'N') + 1) == 'O'
		&& *(ft_strchr(line, 'O') + 1) == ' ')
	{
		if (!(res->no == NULL))
			ft_exit("Double declaration of north texture.");
		res->no = ft_getpath(ft_strchr(line, 'O') + 1);
	}
	else if (ft_strchr(line, 'S') && *(ft_strchr(line, 'S') + 1) == 'O'
			&& *(ft_strchr(line, 'O') + 1) == ' ')
	{
		if (!(res->so == NULL))
			ft_exit("Double declaration of south texture.");
		res->so = ft_getpath(ft_strchr(line, 'O') + 1);
	}
	else if (ft_strchr(line, 'W') && *(ft_strchr(line, 'W') + 1) == 'E'
			&& *(ft_strchr(line, 'E') + 1) == ' ')
	{
		if (!(res->we == NULL))
			ft_exit("Double declaration of west texture.");
		res->we = ft_getpath(ft_strchr(line, 'E') + 1);
	}
}

void	ft_gettexture2(t_parsed *res, char *line)
{
	if (ft_strchr(line, 'E') && *(ft_strchr(line, 'E') + 1) == 'A'
			&& *(ft_strchr(line, 'A') + 1) == ' ')
	{
		if (!(res->ea == NULL))
			ft_exit("Double declaration of east texture.");
		res->ea = ft_getpath(ft_strchr(line, 'A') + 1);
	}
	else if (ft_strchr(line, 'S') && *(ft_strchr(line, 'S') + 1) == ' ')
	{
		if (!(res->spr == NULL))
			ft_exit("Double declaration of sprite texture.");
		res->spr = ft_getpath(ft_strchr(line, 'S') + 1);
	}
}

void	ft_getcolors(t_parsed *res, char *line)
{
	if (ft_strchr(line, 'F') && *(ft_strchr(line, 'F') + 1) == ' ')
	{
		if (!(res->fcolor < 0))
			ft_exit("Double declaration of floor color.");
		res->fcolor = ft_gettrgb(ft_fetchdigit(ft_strchr(line, 'F') + 1));
	}
	else if (ft_strchr(line, 'C') && *(ft_strchr(line, 'C') + 1) == ' ')
	{
		if (!(res->ccolor < 0))
			ft_exit("Double declaration of ceiling color.");
		res->ccolor = ft_gettrgb(ft_fetchdigit(ft_strchr(line, 'C') + 1));
	}
}
