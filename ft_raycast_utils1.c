/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 18:13:23 by aisraely          #+#    #+#             */
/*   Updated: 2021/05/11 18:13:36 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_setray(t_parsed *res)
{
	res->ray.camx = 2 * res->i / (double)res->w - 1;
	res->ray.dirx = res->player.dirx + res->player.planex * res->ray.camx;
	res->ray.diry = res->player.diry + res->player.planey * res->ray.camx;
	res->ray.mapx = (int)res->player.posx;
	res->ray.mapy = (int)res->player.posy;
	res->ray.deltax = fabs(1 / res->ray.dirx);
	res->ray.deltay = fabs(1 / res->ray.diry);
	res->ray.hit = 0;
}

void	ft_setstep(t_parsed *res)
{
	if (res->ray.dirx < 0)
	{
		res->ray.stepx = -1;
		res->ray.sidedistx = (res->player.posx - res->ray.mapx) *
			res->ray.deltax;
	}
	else
	{
		res->ray.stepx = 1;
		res->ray.sidedistx = (res->ray.mapx + 1.0 - res->player.posx) *
			res->ray.deltax;
	}
	if (res->ray.diry < 0)
	{
		res->ray.stepy = -1;
		res->ray.sidedisty = (res->player.posy - res->ray.mapy) *
			res->ray.deltay;
	}
	else
	{
		res->ray.stepy = 1;
		res->ray.sidedisty = (res->ray.mapy + 1.0 - res->player.posy) *
			res->ray.deltay;
	}
}

void	ft_performdda(t_parsed *res)
{
	if (res->ray.sidedistx < res->ray.sidedisty)
	{
		res->ray.sidedistx += res->ray.deltax;
		res->ray.mapx += res->ray.stepx;
		if (res->ray.dirx < 0)
			res->ray.side = 'S';
		else if (res->ray.dirx > 0)
			res->ray.side = 'N';
	}
	else
	{
		res->ray.sidedisty += res->ray.deltay;
		res->ray.mapy += res->ray.stepy;
		if (res->ray.diry < 0)
			res->ray.side = 'E';
		else if (res->ray.diry > 0)
			res->ray.side = 'W';
	}
	if (res->map.m[res->ray.mapx][res->ray.mapy] == 1)
		res->ray.hit = 1;
}

void	ft_domath1(t_parsed *res)
{
	if (res->ray.side == 'S' || res->ray.side == 'N')
		res->ray.walldist = (res->ray.mapx - res->player.posx +
				(1 - res->ray.stepx) / 2) / res->ray.dirx;
	else if (res->ray.side == 'W' || res->ray.side == 'E')
		res->ray.walldist = (res->ray.mapy - res->player.posy +
				(1 - res->ray.stepy) / 2) / res->ray.diry;
	res->ray.lineheight = (int)(res->h / res->ray.walldist);
	res->ray.drawstart = -res->ray.lineheight / 2 + res->h / 2;
	if (res->ray.drawstart < 0)
		res->ray.drawstart = 0;
	res->ray.drawend = res->ray.lineheight / 2 + res->h / 2;
	if (res->ray.drawend < 0)
		res->ray.drawend = res->h - 1;
	if (res->ray.side == 'N' || res->ray.side == 'S')
		res->ray.wallx = res->player.posy + res->ray.walldist * res->ray.diry;
	else if (res->ray.side == 'W' || res->ray.side == 'E')
		res->ray.wallx = res->player.posx + res->ray.walldist * res->ray.dirx;
	res->ray.wallx -= floor(res->ray.wallx);
	res->ray.texx = (int)(res->ray.wallx * (double)res->texno.width);
	if ((res->ray.side == 'N' || res->ray.side == 'S') && res->ray.dirx > 0)
		res->ray.texx = res->texno.width - res->ray.texx - 1;
	if ((res->ray.side == 'W' || res->ray.side == 'E') && res->ray.diry < 0)
		res->ray.texx = res->texno.width - res->ray.texx - 1;
	res->zbuffer[res->i] = res->ray.walldist;
}

void	ft_domath2(t_parsed *res)
{
	res->ray.spritex = res->sprites[res->i]->posx - res->player.posx;
	res->ray.spritey = res->sprites[res->i]->posy - res->player.posy;
	res->ray.invdet = 1.0 / (res->player.planex * res->player.diry -
					res->player.planey * res->player.dirx);
	res->ray.transx = res->ray.invdet * (res->player.diry *
			res->ray.spritex - res->player.dirx * res->ray.spritey);
	res->ray.transy = res->ray.invdet * (-res->player.planey *
			res->ray.spritex + res->player.planex * res->ray.spritey);
	res->ray.sprx = (int)(res->w / 2 * (1 + res->ray.transx / res->ray.transy));
	res->ray.sprheight = abs((int)(res->h / res->ray.transy));
	res->ray.drawstarty = -res->ray.sprheight / 2 + res->h / 2;
	if (res->ray.drawstarty < 0)
		res->ray.drawstarty = 0;
	res->ray.drawendy = res->ray.sprheight / 2 + res->h / 2;
	if (res->ray.drawendy >= res->h)
		res->ray.drawendy = res->h - 1;
	res->ray.sprwidth = abs((int)(res->h / res->ray.transy));
	res->ray.drawstartx = -res->ray.sprwidth / 2 + res->ray.sprx;
	if (res->ray.drawstartx < 0)
		res->ray.drawstartx = 0;
	res->ray.drawendx = res->ray.sprwidth / 2 + res->ray.sprx;
	if (res->ray.drawendx >= res->w)
		res->ray.drawendx = res->w - 1;
}
