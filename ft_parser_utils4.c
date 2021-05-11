/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 21:18:42 by aisraely          #+#    #+#             */
/*   Updated: 2021/05/10 21:27:28 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_setdirvector(t_parsed *res, char d)
{
	if (d == 'N')
	{
		res->player.dirx = -1;
		res->player.diry = 0;
	}
	else if (d == 'S')
	{
		res->player.dirx = 1;
		res->player.diry = 0;
	}
	else if (d == 'E')
	{
		res->player.dirx = 0;
		res->player.diry = 1;
	}
	else if (d == 'W')
	{
		res->player.dirx = 0;
		res->player.diry = -1;
	}
}

void	ft_setcamplane(t_parsed *res, char d)
{
	if (d == 'N')
	{
		res->player.planex = 0;
		res->player.planey = FIELD_OF_VIEW;
	}
	else if (d == 'S')
	{
		res->player.planex = 0;
		res->player.planey = -FIELD_OF_VIEW;
	}
	else if (d == 'E')
	{
		res->player.planex = FIELD_OF_VIEW;
		res->player.planey = 0;
	}
	else if (d == 'W')
	{
		res->player.planex = -FIELD_OF_VIEW;
		res->player.planey = 0;
	}
}

void	ft_checkdimensions(t_parsed *res)
{
	if (!(res->texno.width == res->texno.height
			&& res->texno.height == res->texso.width
			&& res->texso.width == res->texso.height
			&& res->texso.height == res->texea.width
			&& res->texea.width == res->texea.height
			&& res->texea.height == res->texwe.width
			&& res->texwe.width == res->texwe.height
			&& res->texwe.height == res->texspr.width
			&& res->texspr.width == res->texspr.height))
		ft_exit("The textures do not possess the same dimensions.");
}

void	ft_loadtextures1(t_parsed *res)
{
	if (!(res->texno.img = mlx_xpm_file_to_image(res->scr.mlx, res->no,
		&res->texno.width, &res->texno.height)))
		ft_exit("Failed to allocate memory for the north texture.");
	free(res->no);
	res->texno.addr = mlx_get_data_addr(res->texno.img, &res->texno.bpp,
		&res->texno.linelen, &res->texno.endian);
	if (!(res->texso.img = mlx_xpm_file_to_image(res->scr.mlx, res->so,
		&(res->texso.width), &(res->texso.height))))
		ft_exit("Failed to allocate memory for the south texture.");
	free(res->so);
	res->texso.addr = mlx_get_data_addr(res->texso.img, &res->texso.bpp,
		&res->texso.linelen, &res->texso.endian);
}

void	ft_loadtextures2(t_parsed *res)
{
	if (!(res->texwe.img = mlx_xpm_file_to_image(res->scr.mlx, res->we,
		&(res->texwe.width), &(res->texwe.height))))
		ft_exit("Failed to allocate memory for the west texture.");
	free(res->we);
	res->texwe.addr = mlx_get_data_addr(res->texwe.img, &res->texwe.bpp,
		&res->texwe.linelen, &res->texwe.endian);
	if (!(res->texea.img = mlx_xpm_file_to_image(res->scr.mlx, res->ea,
		&(res->texea.width), &(res->texea.height))))
		ft_exit("Failed to allocate memory for the east texture.");
	free(res->ea);
	res->texea.addr = mlx_get_data_addr(res->texea.img, &res->texea.bpp,
		&res->texea.linelen, &res->texea.endian);
	if (!(res->texspr.img = mlx_xpm_file_to_image(res->scr.mlx, res->spr,
		&(res->texspr.width), &(res->texspr.height))))
		ft_exit("Failed to allocate memory for the sprite.");
	free(res->spr);
	res->texspr.addr = mlx_get_data_addr(res->texspr.img, &res->texspr.bpp,
		&res->texspr.linelen, &res->texspr.endian);
}
