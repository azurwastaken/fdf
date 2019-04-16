/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaseaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 15:21:05 by mcaseaux          #+#    #+#             */
/*   Updated: 2018/05/25 17:23:20 by mcaseaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			key_pressed(int code, t_mlxinfo *ptr)
{
	if (code == 53)
	{
		mlx_destroy_window(ptr->mlx_ptr, ptr->win_ptr);
		exit(1);
	}
	return (0);
}

int			ft_error(void)
{
	if (errno == 2)
		ft_putendl("error : File don't exist / Incorrect File");
	if (errno == 13)
		ft_putendl("error : You dont have right to read this file");
	return (0);
}

int			main(int ac, char **av)
{
	t_mlxinfo	*ptr;
	t_filespec	*filespec;
	t_dot		**grid;
	int			**z_tab;

	if (ac != 2)
	{
		ft_putendl("usage: ./fdf <fdf_file>");
		return (0);
	}
	if (!(ptr = malloc(sizeof(t_mlxinfo))))
		return (0);
	if (!(filespec = malloc(sizeof(t_filespec))))
		return (0);
	if ((z_tab = file_to_tab(av[1], filespec)) == NULL)
		return (ft_error());
	grid = ft_create_grid(filespec);
	grid = ft_fusion(grid, z_tab, filespec);
	ptr->mlx_ptr = mlx_init();
	ptr->win_ptr = mlx_new_window(ptr->mlx_ptr, 2048, 1152, "FdF");
	trace_grid(grid, filespec, ptr, z_tab);
	mlx_key_hook(ptr->win_ptr, key_pressed, ptr);
	mlx_loop(ptr->mlx_ptr);
	return (0);
}
