/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaseaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 17:43:35 by mcaseaux          #+#    #+#             */
/*   Updated: 2018/05/21 17:43:36 by mcaseaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				vabs(int nbr)
{
	return (nbr > 0 ? nbr : -nbr);
}

static double	get_coef(int **z_tab, t_filespec *fspc)
{
	int		altmax;
	int		i;
	int		j;
	double	coef;

	i = 0;
	altmax = vabs(z_tab[0][0]);
	while (i < fspc->nbln)
	{
		j = 0;
		while (j < fspc->nbcarmax)
		{
			if (vabs(z_tab[i][j]) > altmax)
				altmax = vabs(z_tab[i][j]);
			j++;
		}
		i++;
	}
	if (altmax == 0)
		return (100);
	coef = 100.0 / (double)altmax;
	return (coef);
}

t_dot			**ft_fusion(t_dot **grid, int **z_tab, t_filespec *fspc)
{
	int		i;
	int		j;
	double	coef;

	i = 0;
	coef = get_coef(z_tab, fspc);
	while (i < fspc->nbln)
	{
		j = 0;
		while (j < fspc->nbcarmax)
		{
			grid[i][j].y -= (coef / 2) * z_tab[i][j];
			grid[i][j].x -= (z_tab[i][j] = coef * z_tab[i][j]);
			j++;
		}
		i++;
	}
	return (grid);
}

static t_dot	**ft_assign_point(t_dot **grid, int i, int j, t_filespec *fspc)
{
	if (fspc->nbcarmax > 1)
		grid[i][j].x = (j * (1024 - 150)) / (fspc->nbcarmax / 2) + 150;
	else
		grid[i][j].x = (j * (1024 - 150)) / (fspc->nbcarmax) + 150;
	if (fspc->nbln > 1)
		grid[i][j].y = (i * (576 - 75)) / (fspc->nbln / 2) + 75;
	else
		grid[i][j].y = (i * (576 - 75)) / (fspc->nbln) + 75;
	return (grid);
}

t_dot			**ft_create_grid(t_filespec *fspc)
{
	t_dot	**grid;
	int		i;
	int		j;

	if (!(grid = (t_dot **)malloc(sizeof(t_dot *) * fspc->nbln)))
		return (0);
	i = 0;
	while (i < fspc->nbln)
	{
		if (!(grid[i] = (t_dot *)malloc(sizeof(t_dot) * fspc->nbcarmax)))
			return (0);
		i++;
	}
	i = 0;
	while (i < fspc->nbln)
	{
		j = 0;
		while (j < fspc->nbcarmax)
		{
			ft_assign_point(grid, i, j, fspc);
			j++;
		}
		i++;
	}
	return (grid);
}
