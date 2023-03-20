# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 13:26:57 by hbui-vu           #+#    #+#              #
#    Updated: 2023/03/20 13:41:13 by hbui-vu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = error.c utils.c mlist.c heredoc.c builtin_commands.c pipex.c testing.c
BSRCS = error.c utils.c mlist.c heredoc.c builtin_commands.c pipex_bonus.c testing.c

CFLAGS = -Wall -Wextra -Werror

CC = cc

LIBFT_DIR = ./libft
FT_PRINTF_DIR = ./ft_printf_err

LIBS = ./libft/libft.a ./ft_printf_err/ftprintf_err.a

OBJS = $(SRCS:.c=.o)
BOBJS = $(BSRCS: .c=.o)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(FT_PRINTF_DIR)
	$(CC) $(OBJS) $(LIBS) $(CFLAGS) -o $(NAME)

all: $(NAME)

bonus: $(NAME) $(BOBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(FT_PRINTF_DIR)
	$(CC) $(BOBJS) $(LIBS) $(CFLAGS) -o $(NAME)
		
clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf *.o

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(FT_PRINTF_DIR)
	rm -rf $(NAME)
	rm -rf $(BNAME)

re: fclean all

.PHONY: all clean fclean re
