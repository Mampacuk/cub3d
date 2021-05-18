/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 21:18:20 by aisraely          #+#    #+#             */
/*   Updated: 2021/05/10 21:18:24 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_check_resources(t_parsed *res)
{
	return (res->w <= 0 || res->h <= 0 || res->so == NULL
	|| res->we == NULL || res->no == NULL || res->ea == NULL
	|| res->spr == NULL || res->fcolor <= 0 || res->ccolor <= 0);
}

void	ft_setup_map(t_parsed *res, char *mappath)
{
	if (ft_check_resources(res))
		ft_exit("One of the fields remains empty.");
	res->map.h = ft_getmapheight(mappath);
	res->map.w = ft_getmapwidth(mappath);
	res->sprnum = ft_getsprnum(mappath);
	if (!(res->sprites = malloc(sizeof(t_sprite*) * res->sprnum)))
		ft_exit("Failed to allocate memory for the sprites.");
	res->i = 0;
	while (res->i < res->sprnum)
		if (!(res->sprites[(res->i)++] = malloc(sizeof(t_sprite))))
			ft_exit("Failed to allocate memory for a sprite.");
	if (res->map.h < 3 || res->map.w < 3)
		ft_exit("Dimensions cannot be less than 3.");
	res->i = 0;
	res->map.m = malloc(res->map.h * sizeof(int*));
	while (res->i < res->map.h)
		res->map.m[(res->i)++] = ft_calloc(res->map.w, sizeof(int));
	res->i = 0;
	if (!(res->zbuffer = malloc(sizeof(double) * res->w)))
		ft_exit("Failed to allocate memory for the zbuffer.");
}

char	*ft_getpath(char *str)
{
	int		i;
	char	*path;

	i = 0;
	while (*str && ft_isspace(*str))
		str++;
	while (*(str + i) && !(ft_isspace(*(str + i))))
		i++;
	if (!(path = malloc(sizeof(char) * (i + 1))))
		ft_exit("Failed to allocate memory for a file path.");
	i = 0;
	while (*(str + i) && !(ft_isspace(*(str + i))))
	{
		*(path + i) = *(str + i);
		i++;
	}
	*(path + i) = '\0';
	if (!(ft_check_extension(path, ".xpm")))
		ft_exit("File specified is not in .xpm format.");
	if (*path == '\0')
		ft_exit("A path for a file is not specified.");
	return (path);
}

void	ft_initplayer(t_parsed *res, char startdir, int posx, int posy)
{
	if (!(res->player.posx < 0 && res->player.posy < 0))
		ft_exit("Multiple players are not permitted.");
	res->player.posx = posx;
	res->player.posy = posy;
	ft_setdirvector(res, startdir);
	ft_setcamplane(res, startdir);
}

void	ft_initparser(t_parsed *res)
{
	res->scr.mlx = mlx_init();
	res->ea = NULL;
	res->no = NULL;
	res->we = NULL;
	res->so = NULL;
	res->spr = NULL;
	res->w = -1;
	res->h = -1;
	res->fcolor = -1;
	res->ccolor = -1;
	res->player.posx = -1;
	res->player.posy = -1;
	res->sprnum = 0;
	res->player.time = 0;
	res->player.oldtime = 0;
	res->player.frametime = 0;
}
