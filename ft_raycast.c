/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 18:32:44 by aisraely          #+#    #+#             */
/*   Updated: 2021/05/11 18:32:45 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_drawsprite(t_parsed *res)
{
	res->i = 0;
	while (res->i < res->sprnum)
	{
		ft_domath2(res);
		res->j = res->ray.drawstartx;
		while (res->j < res->ray.drawendx)
			ft_putspritestripe(res);
		res->i++;
	}
}

void	ft_drawwall(t_parsed *res, int stripe, int y)
{
	res->ray.texy = (int)res->ray.texpos & (res->texno.height - 1);
	res->ray.texpos += res->ray.texstep;
	if (res->ray.side == 'N')
		ft_mlx_pixel_put(&(res->scr), stripe, y,
		ft_mlx_get_color(&res->texno, res->ray.texx, res->ray.texy));
	else if (res->ray.side == 'S')
		ft_mlx_pixel_put(&(res->scr), stripe, y,
		ft_mlx_get_color(&res->texso, res->ray.texx, res->ray.texy));
	else if (res->ray.side == 'W')
		ft_mlx_pixel_put(&(res->scr), stripe, y,
	ft_mlx_get_color(&res->texwe, res->ray.texx, res->ray.texy) / 2);
	else if (res->ray.side == 'E')
		ft_mlx_pixel_put(&(res->scr), stripe, y,
	ft_mlx_get_color(&res->texea, res->ray.texx, res->ray.texy) / 2);
}

void	ft_renderframe(t_parsed *res)
{
	res->i = 0;
	while (res->i < res->w)
	{
		ft_setray(res);
		ft_setstep(res);
		while (!res->ray.hit)
			ft_performdda(res);
		ft_domath1(res);
		ft_mlx_stripe_put(res, res->i, res->ray.drawstart, res->ray.drawend);
		res->i++;
	}
	res->i = 0;
	while (res->i < res->sprnum)
	{
		res->sprites[res->i]->dist = ft_squared(res->player.posx -
			res->sprites[res->i]->posx)
			+ ft_squared(res->player.posy - res->sprites[res->i]->posy);
		(res->i)++;
	}
	ft_quicksort(res->sprites, 0, res->sprnum - 1);
	ft_drawsprite(res);
	res->player.oldtime = res->player.time;
	res->player.time = (double)(clock()) / CLOCKS_PER_SEC;
	res->player.frametime = res->player.time - res->player.oldtime;
}

int		ft_raycast(t_parsed *res)
{
	res->player.movespeed = res->player.frametime * 20.0;
	res->player.rotspeed = res->player.frametime * 12.0;
	ft_receiveinput1(res);
	ft_receiveinput2(res);
	ft_receiveinput3(res);
	ft_receiveinput4(res);
	ft_renderframe(res);
	if (res->bmp)
		ft_createbmp(res);
	mlx_put_image_to_window(res->scr.mlx, res->scr.win, res->scr.img.img, 0, 0);
	mlx_do_sync(res->scr.mlx);
	return (0);
}
