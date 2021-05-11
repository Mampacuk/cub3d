/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 18:45:59 by aisraely          #+#    #+#             */
/*   Updated: 2021/05/11 18:46:00 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ft_mlx_pixel_put(t_screen *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.linelen + x * (data->img.bpp / 8));
	*(unsigned int*)dst = color;
}

unsigned int	ft_mlx_get_color(t_img *imgstruct, int x, int y)
{
	char	*dst;

	dst = imgstruct->addr + (y * imgstruct->linelen + x * (imgstruct->bpp / 8));
	return (*(unsigned int*)dst);
}

void			ft_mlx_stripe_put(t_parsed *res, int stripe, int ds, int de)
{
	int y;

	y = 0;
	res->ray.texstep = 1.0 * res->texno.height / res->ray.lineheight;
	res->ray.texpos = (ds - res->h / 2 + res->ray.lineheight / 2)
		* res->ray.texstep;
	while (y < res->h)
	{
		if (y >= 0 && y < ds)
			ft_mlx_pixel_put(&res->scr, stripe, y, res->ccolor);
		else if (y >= ds && y < de)
			ft_drawwall(res, stripe, y);
		else if (y >= de)
			ft_mlx_pixel_put(&res->scr, stripe, y, res->fcolor);
		y++;
	}
}

int				ft_mlx_pressed(int keycode, t_keys *keys)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 13)
		keys->movefor = 1;
	if (keycode == 1)
		keys->moveback = 1;
	if (keycode == 0)
		keys->moveright = 1;
	if (keycode == 2)
		keys->moveleft = 1;
	if (keycode == 123)
		keys->turnright = 1;
	if (keycode == 124)
		keys->turnleft = 1;
	return (0);
}

int				ft_mlx_released(int keycode, t_keys *keys)
{
	if (keycode == 13)
		keys->movefor = 0;
	if (keycode == 1)
		keys->moveback = 0;
	if (keycode == 0)
		keys->moveright = 0;
	if (keycode == 2)
		keys->moveleft = 0;
	if (keycode == 123)
		keys->turnright = 0;
	if (keycode == 124)
		keys->turnleft = 0;
	return (0);
}
