/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 21:32:17 by aisraely          #+#    #+#             */
/*   Updated: 2021/05/10 21:32:18 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_swap(t_sprite **arr, int firstindex, int secondindex)
{
	t_sprite	*temp;

	temp = arr[firstindex];
	arr[firstindex] = arr[secondindex];
	arr[secondindex] = temp;
}

static int	ft_partition(t_sprite **arr, int p, int r)
{
	int q;
	int i;

	i = p;
	q = p;
	while (i < r)
	{
		if (arr[i]->dist >= arr[r]->dist)
			ft_swap(arr, q++, i);
		i++;
	}
	ft_swap(arr, r, q);
	return (q);
}

void		ft_quicksort(t_sprite **arr, int p, int r)
{
	int q;

	q = 0;
	if (p < r)
	{
		q = ft_partition(arr, p, r);
		ft_quicksort(arr, p, q - 1);
		ft_quicksort(arr, q + 1, r);
	}
}

double		ft_squared(double num)
{
	return (num * num);
}
