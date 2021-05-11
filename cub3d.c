/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 19:23:56 by aisraely          #+#    #+#             */
/*   Updated: 2021/05/09 19:26:16 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_parsed	test;

	if (argc > 3 || argc == 1)
		ft_exit("Invalid number of arguments.");
	if (argc == 3)
	{
		if (ft_strlen(argv[2]) == 6 && ft_strncmp(argv[2], "--save", 6) == 0)
			test.bmp = 1;
		else
			ft_exit("Unknown command in the second argument.");
	}
	if (!(ft_check_extension(argv[1], ".cub")))
		ft_exit("Invalid file format.");
	test = ft_parser(argv[1]);
	test.scr.win = mlx_new_window(test.scr.mlx, test.w, test.h, "cub3D");
	test.scr.img.img = mlx_new_image(test.scr.mlx, test.w, test.h);
	test.scr.img.addr = mlx_get_data_addr(test.scr.img.img,
	&test.scr.img.bpp, &test.scr.img.linelen, &test.scr.img.endian);
	mlx_hook(test.scr.win, 2, 1L << 0, ft_mlx_pressed, &(test.keys));
	mlx_hook(test.scr.win, 3, 1L << 1, ft_mlx_released, &(test.keys));
	mlx_loop_hook(test.scr.mlx, ft_raycast, &test);
	mlx_loop(test.scr.mlx);
}
