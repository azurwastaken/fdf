/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaseaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 15:27:38 by mcaseaux          #+#    #+#             */
/*   Updated: 2018/05/21 15:27:42 by mcaseaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include "get_next_line.h"
# include <errno.h>

typedef struct		s_dot
{
	int				x;
	int				y;
}					t_dot;

typedef	struct		s_mlxinfo
{
	void			*win_ptr;
	void			*mlx_ptr;
}					t_mlxinfo;

typedef struct		s_filespec
{
	int				nbln;
	int				nbcarmax;
	char			**file;
}					t_filespec;

void				ft_swap_pos(int *xa, int *xb, int *ya, int *yb);
void				ft_relie(t_mlxinfo *ptr, t_dot dota, t_dot dotb,
					int color);
int					**file_to_tab(char *path, t_filespec *fspc);
int					ft_filelen(char *path);
t_dot				**ft_create_grid(t_filespec *fspc);
void				trace_grid(t_dot **grid, t_filespec *fspc,
					t_mlxinfo *ptr, int **z_tab);
t_dot				**ft_fusion(t_dot **grid, int **z_tab,
					t_filespec *fspc);
int					vabs(int nbr);

#endif
