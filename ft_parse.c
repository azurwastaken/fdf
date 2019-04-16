/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaseaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 15:36:47 by mcaseaux          #+#    #+#             */
/*   Updated: 2018/05/21 15:36:51 by mcaseaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				ft_filelen(char *path)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	if ((fd = open(path, O_RDONLY)) <= 0)
		return (0);
	while (get_next_line(fd, &line) == 1)
	{
		i++;
		free(line);
	}
	free(line);
	close(fd);
	return (i);
}

static int		get_point_ref(char **split, int fd)
{
	int		i;
	char	*line;

	i = 0;
	get_next_line(fd, &line);
	split = ft_strsplit(line, ' ');
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
	free(line);
	return (i);
}

static int		ft_countcar(char *path)
{
	int		fd;
	int		i;
	int		max;
	char	*line;
	char	**split;

	split = NULL;
	if ((fd = open(path, O_RDONLY)) <= 0)
		return (0);
	max = get_point_ref(split, fd);
	i = max;
	while (get_next_line(fd, &line) == 1)
	{
		i = 0;
		split = ft_strsplit(line, ' ');
		while (split[i] != NULL)
			free(split[i++]);
		if (i != max)
			return (0);
		free(line);
		free(split);
	}
	close(fd);
	free(line);
	return (i);
}

static int		**from_file_to_y(int fd, int **y_tab, t_filespec *fspc)
{
	int		i;
	int		j;
	char	*line;
	char	**split;

	j = 0;
	while (get_next_line(fd, &line) == 1 && j < fspc->nbln)
	{
		split = ft_strsplit(line, ' ');
		i = 0;
		if (!(y_tab[j] = (int *)malloc(sizeof(int) * (fspc->nbcarmax + 1))))
			return (0);
		while (split[i] != NULL)
		{
			y_tab[j][i] = ft_atoi(split[i]);
			free(split[i]);
			i++;
		}
		free(split);
		free(line);
		j++;
	}
	free(line);
	return (y_tab);
}

int				**file_to_tab(char *path, t_filespec *fspc)
{
	int		fd;
	int		**y_tab;

	fspc->nbln = ft_filelen(path);
	if (!(fspc->nbcarmax = ft_countcar(path)))
		return (NULL);
	if ((fd = open(path, O_RDONLY)) <= 0)
		return (0);
	if (!(y_tab = (int **)malloc(sizeof(int *) * fspc->nbln)))
		return (0);
	return (from_file_to_y(fd, y_tab, fspc));
}
