/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 21:51:33 by aisraely          #+#    #+#             */
/*   Updated: 2021/05/10 21:51:34 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_parsed	ft_parser(char *mappath)
{
	t_parsed	res;
	int			fd;
	char		*line;

	ft_initparser(&res);
	fd = open(mappath, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		ft_getresolution(&res, line);
		ft_gettexture1(&res, line);
		ft_gettexture2(&res, line);
		ft_getcolors(&res, line);
	}
	ft_getworldmap(mappath, &res);
	ft_loadtextures1(&res);
	ft_loadtextures2(&res);
	ft_checkdimensions(&res);
	free(line);
	close(fd);
	return (res);
}
