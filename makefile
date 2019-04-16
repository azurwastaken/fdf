# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcaseaux <mcaseaux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/22 14:14:51 by mcaseaux          #+#    #+#              #
#    Updated: 2018/03/14 12:21:52 by mcaseaux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
LIB = ./libft/libft.a
SRCS = get_next_line.c trace.c main.c ft_parse.c init.c draw.c
OBJS = get_next_line.o trace.o main.o ft_parse.o init.o draw.o

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	make -C libft/ clean
	gcc -Wall -Wextra -Werror $(SRCS) $(LIB) -o $(NAME) -I /usr/local/include  -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

clean:
	/bin/rm -f $(OBJS)
	make -C libft/ clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C libft/ fclean

re: fclean all
