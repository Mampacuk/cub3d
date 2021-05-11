/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 18:30:32 by aisraely          #+#    #+#             */
/*   Updated: 2021/05/11 18:30:33 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putspritestripe(t_parsed *res)
{
	res->ray.texx = (int)(256 * (res->j - (-res->ray.sprwidth / 2 +
		res->ray.sprx)) * res->texspr.width / res->ray.sprwidth) / 256;
	if (res->ray.transy > 0 && res->j > 0 && res->j < res->w &&
			res->ray.transy < res->zbuffer[res->j])
	{
		res->y = res->ray.drawstarty;
		while (res->y < res->ray.drawendy)
		{
			res->d = res->y * 256 - res->h * 128 + res->ray.sprheight * 128;
			res->ray.texy = ((res->d * res->texspr.height) / res->ray.sprheight)
				/ 256;
			if (ft_mlx_get_color(&res->texspr, res->ray.texx, res->ray.texy))
				ft_mlx_pixel_put(&(res->scr), res->j, res->y,
				ft_mlx_get_color(&res->texspr, res->ray.texx, res->ray.texy));
			(res->y)++;
		}
	}
	res->j++;
}

void	ft_receiveinput1(t_parsed *res)
{
	if (res->keys.movefor)
	{
		if (!(res->map.m[(int)(res->player.posx + res->player.dirx *
			res->player.movespeed)][(int)(res->player.posy)] == 1))
			res->player.posx += res->player.dirx * res->player.movespeed;
		if (!(res->map.m[(int)res->player.posx][(int)(res->player.posy
			+ res->player.diry * res->player.movespeed)] == 1))
			res->player.posy += res->player.diry * res->player.movespeed;
	}
	if (res->keys.moveback)
	{
		if (!(res->map.m[(int)(res->player.posx - res->player.dirx *
			res->player.movespeed)][(int)(res->player.posy)] == 1))
			res->player.posx -= res->player.dirx * res->player.movespeed;
		if (!(res->map.m[(int)res->player.posx][(int)(res->player.posy -
			res->player.diry * res->player.movespeed)] == 1))
			res->player.posy -= res->player.diry * res->player.movespeed;
	}
}

void	ft_receiveinput2(t_parsed *res)
{
	if (res->keys.moveright)
	{
		if (!(res->map.m[(int)(res->player.posx - res->player.diry *
			res->player.movespeed)][(int)(res->player.posy)] == 1))
			res->player.posx -= res->player.diry * res->player.movespeed;
		if (!(res->map.m[(int)res->player.posx][(int)(res->player.posy +
			res->player.dirx * res->player.movespeed)] == 1))
			res->player.posy += res->player.dirx * res->player.movespeed;
	}
	if (res->keys.moveleft)
	{
		if (!(res->map.m[(int)(res->player.posx + res->player.diry *
			res->player.movespeed)][(int)(res->player.posy)] == 1))
			res->player.posx += res->player.diry * res->player.movespeed;
		if (!(res->map.m[(int)res->player.posx][(int)(res->player.posy -
			res->player.dirx * res->player.movespeed)] == 1))
			res->player.posy -= res->player.dirx * res->player.movespeed;
	}
}

void	ft_receiveinput3(t_parsed *res)
{
	if (res->keys.turnleft)
	{
		res->player.olddirx = res->player.dirx;
		res->player.dirx = res->player.dirx * cos(-(res->player.rotspeed))
			- res->player.diry * sin(-(res->player.rotspeed));
		res->player.diry = res->player.olddirx * sin(-(res->player.rotspeed))
			+ res->player.diry * cos(-(res->player.rotspeed));
		res->player.oldplanex = res->player.planex;
		res->player.planex = res->player.planex * cos(-(res->player.rotspeed))
			- res->player.planey * sin(-(res->player.rotspeed));
		res->player.planey = res->player.oldplanex *
			sin(-(res->player.rotspeed)) + res->player.planey *
			cos(-(res->player.rotspeed));
	}
}

void	ft_receiveinput4(t_parsed *res)
{
	if (res->keys.turnright)
	{
		res->player.olddirx = res->player.dirx;
		res->player.dirx = res->player.dirx * cos(res->player.rotspeed) -
			res->player.diry * sin(res->player.rotspeed);
		res->player.diry = res->player.olddirx * sin(res->player.rotspeed) +
			res->player.diry * cos(res->player.rotspeed);
		res->player.oldplanex = res->player.planex;
		res->player.planex = res->player.planex * cos(res->player.rotspeed) -
			res->player.planey * sin(res->player.rotspeed);
		res->player.planey = res->player.oldplanex * sin(res->player.rotspeed) +
			res->player.planey * cos(res->player.rotspeed);
	}
}
