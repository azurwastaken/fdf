/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaseaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:15:49 by mcaseaux          #+#    #+#             */
/*   Updated: 2018/03/07 14:50:44 by mcaseaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "./libft/libft.h"
# include <string.h>
# include <fcntl.h>

# define BUFF_SIZE 10000

int	get_next_line(int fd, char **line);

#endif
