/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaseaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 15:32:46 by mcaseaux          #+#    #+#             */
/*   Updated: 2018/05/21 15:32:47 by mcaseaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			ft_swap_pos(int *xa, int *xb, int *ya, int *yb)
{
	int tmp;

	tmp = *xa;
	*xa = *xb;
	*xb = tmp;
	tmp = *ya;
	*ya = *yb;
	*yb = tmp;
}

static void		ft_drwcol(t_mlxinfo *ptr, t_dot a, int length, int color)
{
	int final;
	int x_start;
	int y_start;

	x_start = a.x;
	y_start = a.y;
	final = y_start + length;
	while (y_start++ < final)
		mlx_pixel_put(ptr->mlx_ptr, ptr->win_ptr, x_start, y_start, color);
}

static void		ft_relie_casun(t_mlxinfo *ptr, t_dot dota,
		t_dot dotb, int color)
{
	int x;

	if (dota.x > dotb.x)
		ft_swap_pos(&dota.x, &dotb.x, &dota.y, &dotb.y);
	x = dota.x;
	while (x <= dotb.x)
	{
		mlx_pixel_put(ptr->mlx_ptr, ptr->win_ptr, x,
				dota.y + ((dotb.y - dota.y) * (x - dota.x)) /
				(dotb.x - dota.x), color);
		x++;
	}
}

static void		ft_relie_casde(t_mlxinfo *ptr, t_dot dota,
		t_dot dotb, int color)
{
	int y;

	if (dota.y > dotb.y)
		ft_swap_pos(&dota.x, &dotb.x, &dota.y, &dotb.y);
	y = dota.y;
	while (y <= dotb.y)
	{
		mlx_pixel_put(ptr->mlx_ptr, ptr->win_ptr,
				dota.x + ((dotb.x - dota.x) * (y - dota.y)) /
				(dotb.y - dota.y), y, color);
		y++;
	}
}

void			ft_relie(t_mlxinfo *ptr, t_dot dota, t_dot dotb, int color)
{
	int cas;

	if (dotb.x - dota.x != 0)
	{
		if (((dotb.y - dota.y) / (dotb.x - dota.x)) > 1 ||
				((dotb.y - dota.y) / (dotb.x - dota.x)) < -1)
			cas = 2;
		else
			cas = 1;
		if (cas == 1)
			ft_relie_casun(ptr, dota, dotb, color);
		else
			ft_relie_casde(ptr, dota, dotb, color);
	}
	else
		ft_drwcol(ptr, dota, dotb.y - dota.y, color);
}
