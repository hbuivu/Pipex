# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/03 11:01:42 by hbui-vu           #+#    #+#              #
#    Updated: 2022/10/03 11:01:42 by hbui-vu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ft_putchar.c ft_putstr.c ft_putnbr.c ft_putunbr.c ft_puthex.c \
		ft_puthexcap.c ft_putmem.c ft_printf.c

CC = gcc
CFLAGS = -Wall -Wextra -Werror
OBJS = $(SRCS:.c=.o)

all: $(NAME)

${NAME}: ${OBJS}
	ar -rc ${NAME} ${OBJS}

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
