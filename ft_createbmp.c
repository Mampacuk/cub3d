/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_createbmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 21:17:56 by aisraely          #+#    #+#             */
/*   Updated: 2021/05/09 21:18:11 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_fillscreen(int fd, t_parsed *res)
{
	int i;
	int j;
	int color;

	i = res->h;
	while (--i >= 0)
	{
		j = -1;
		while (++j < res->w)
		{
			color = ft_mlx_get_color(&(res->scr.img), j, i);
			write(fd, &color, 4);
		}
	}
	exit(0);
}

static void	ft_screenshot_norm_two(int fd, int all_pix, int zero, int size)
{
	write(fd, &zero, 4);
	write(fd, &size, 4);
	all_pix = 1000;
	write(fd, &all_pix, 4);
	write(fd, &all_pix, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
}

static void	ft_screenshot_norm_one(int fd)
{
	short	plane;

	plane = 1;
	write(fd, &plane, 2);
	plane = 32;
	write(fd, &plane, 2);
}

void		ft_createbmp(t_parsed *res)
{
	int		fd;
	int		all_pix;
	int		zero;
	int		pos_pix;
	int		size;

	fd = open("cub3D.bmp", O_CREAT | O_RDWR, 0666);
	all_pix = res->w * res->h * 4 + 54;
	zero = 0;
	pos_pix = 54;
	size = res->w * res->h;
	write(fd, "BM", 2);
	write(fd, &all_pix, 4);
	write(fd, &zero, 4);
	write(fd, &pos_pix, 4);
	pos_pix = 40;
	write(fd, &pos_pix, 4);
	write(fd, &res->w, 4);
	write(fd, &res->h, 4);
	ft_screenshot_norm_one(fd);
	ft_screenshot_norm_two(fd, all_pix, zero, size);
	ft_fillscreen(fd, res);
}
