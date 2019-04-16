/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaseaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 15:54:13 by mcaseaux          #+#    #+#             */
/*   Updated: 2018/05/29 14:59:24 by mcaseaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			ft_get_scaling(t_filespec *fspc, int cas)
{
	int i;

	i = 1;
	if (cas == 1)
	{
		while ((fspc->nbcarmax / i) > 1024)
			i++;
	}
	else
	{
		while ((fspc->nbln / i) > 576)
			i++;
	}
	return (i);
}

int			rgb_to_code(int r, int g, int b)
{
	int color;

	color = (r * 0x010000) + (g * 0x0100) + b;
	return (color);
}

int			get_color(int za, int zb)
{
	if (za <= 0 && zb <= 0)
		return (0x0000B6);
	za = vabs(za);
	zb = vabs(zb);
	if (za > zb)
		return (rgb_to_code(za * 1.5, 50 + 200 / za, 0));
	else
		return (rgb_to_code(zb * 1.5, 50 + 200 / zb, 0));
}

static int	dot_case(t_filespec *fspc, t_mlxinfo *ptr)
{
	if (fspc->nbcarmax == 1 && fspc->nbln == 1)
	{
		mlx_pixel_put(ptr->mlx_ptr, ptr->win_ptr, 1024, 576, 0x0000B6);
		return (1);
	}
	return (0);
}

void		trace_grid(t_dot **grid, t_filespec *fspc, t_mlxinfo *ptr,
			int **z_tab)
{
	int i;
	int j;

	i = 0;
	if (dot_case(fspc, ptr))
		return ;
	while (i < fspc->nbln)
	{
		j = 0;
		while (j < fspc->nbcarmax)
		{
			if (j + 1 < fspc->nbcarmax)
			{
				ft_relie(ptr, grid[i][j], grid[i][j + 1],
					get_color(z_tab[i][j], z_tab[i][j + 1]));
			}
			if (i + 1 < fspc->nbln)
				ft_relie(ptr, grid[i][j], grid[i + 1][j],
					get_color(z_tab[i][j], z_tab[i + 1][j]));
			j++;
		}
		i++;
	}
}
