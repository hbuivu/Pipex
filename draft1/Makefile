# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 13:26:57 by hbui-vu           #+#    #+#              #
#    Updated: 2023/02/23 13:41:47 by hbui-vu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = error.c free.c find_path.c pipex2.c

CFLAGS = -Wall -Wextra -Werror

CC = cc

LIBFT_DIR = ./libft

LIBS = ./libft/libft.a

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(OBJS) $(LIBS) $(CFLAGS) -o $(NAME)

all: $(NAME)
		
clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf *.o

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

# note: in linux, cc objs libs flags -o name
# in mac, cc libs flags objs -o name