/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaseaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 12:26:50 by mcaseaux          #+#    #+#             */
/*   Updated: 2018/02/15 11:42:29 by mcaseaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_is_bn(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static int		ft_get_bn_pos(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

static int		ft_strgetline(char **line, char const *buff)
{
	char	*new;
	int		npos;

	if ((npos = ft_get_bn_pos((char *)buff)) < 0)
		return (-1);
	if (!(new = ft_strnew(ft_strlen(*line) + npos)))
		return (-1);
	ft_strcpy(new, *line);
	free(*line);
	ft_strncat(new, buff, npos);
	ft_strcpy((char *)buff, &(buff[(buff[npos] == '\n') ? (npos + 1) : npos]));
	*line = new;
	return (0);
}

int				get_next_line(int const fd, char **line)
{
	static char	buff[BUFF_SIZE + 1];
	int			ret;
	int			backn;

	ret = 0;
	if (fd == -1 || !line || !(*line = ft_strnew(100000)) || BUFF_SIZE <= 0)
		return (-1);
	while (1)
	{
		if (!buff[0])
			ft_bzero(buff, BUFF_SIZE + 1);
		if (!buff[0] && (ret = read(fd, buff, BUFF_SIZE)) < 0)
			return (-1);
		if (!ret && **line)
			return (1);
		if (!ret && !buff[0])
			return (0);
		if ((backn = ft_is_bn(buff)) < 0 || ft_strgetline(line, buff) < 0)
			return (-1);
		if (backn)
			return (1);
	}
}
