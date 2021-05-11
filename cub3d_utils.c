/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 20:52:38 by aisraely          #+#    #+#             */
/*   Updated: 2021/05/11 18:47:35 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_exit(char *error)
{
	write(1, "[cub3D] Error: ", 15);
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	exit(0);
}

char	*ft_fetchdigit(char *str)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (ft_isdigit(*str))
			return (str);
		str++;
	}
	return (NULL);
}

int		ft_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int		ft_gettrgb(char *str)
{
	int	r;
	int	g;
	int	b;

	if (!str)
		ft_exit("RGB is empty.");
	r = ft_atoi(str);
	while (*str && ft_isdigit(*str))
		str++;
	while (*str && !(ft_isdigit(*str)))
		str++;
	if (!(ft_isdigit(*str)))
		ft_exit("G of RGB is not found.");
	g = ft_atoi(str);
	while (*str && ft_isdigit(*str))
		str++;
	while (*str && !(ft_isdigit(*str)))
		str++;
	if (!(ft_isdigit(*str)))
		ft_exit("B of RGB is not found.");
	b = ft_atoi(str);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		ft_exit("Number specified for a color is out of range of RGB values.");
	return (ft_trgb(0x0, r, g, b));
}

int		ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (*(str + i))
		i++;
	return (i);
}
