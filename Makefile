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

SRCS = error.c mlist.c pipex.c
BSRCS = error.c bonus_mlist.c bonus_pipex.c bonus_heredoc.c

CFLAGS = -Wall -Wextra -Werror

CC = cc

LIBFT_DIR = ./libft
FT_PRINTF_DIR = ./ft_printf

LIBS = ./libft/libft.a ./ft_printf/libftprintf.a

OBJS = $(SRCS:.c=.o)
BOBJS = $(BSRCS: .c=.o)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(FT_PRINTF_DIR)
	$(CC) $(OBJS) $(LIBS) $(CFLAGS) -o $(NAME)

$(NAME): $(BOBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(FT_PRINTF_DIR)
	$(CC) $(BOBJS) $(LIBS) $(CFLAGS) -o $(NAME)

all: $(NAME)

bonus: $(BNAME)
		
clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf *.o

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)
	rm -rf $(BNAME)

re: fclean all

.PHONY: all clean fclean re

# note: in linux, cc objs libs flags -o name
# in mac, cc libs flags objs -o name