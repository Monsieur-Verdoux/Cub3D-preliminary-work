# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akovalev <akovalev@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/29 17:34:25 by akovalev          #+#    #+#              #
#    Updated: 2024/05/29 17:37:58 by akovalev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= cub3d
CFLAGS	:= -Wall -Wextra -Werror -Wunreachable-code -Ofast
#LIBMLX	:= ./MLX42

#HEADERS	:= -I $(LIBMLX)/include
#LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -pthread -lm -L/Users/$(USER)/.brew/Cellar/glfw/3.3.8/lib -lglfw

SRCS	:=	parsing.c
			
OBJS	:= ${SRCS:.c=.o} Libft/libft.a

all: $(NAME)

#libmlx:
#	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< 
#$(HEADERS)

$(NAME): $(OBJS) #libmlx
	@$(CC) $(OBJS) -o $(NAME)
#$(LIBS) (HEADERS)
Libft/libft.a:
	@$(MAKE) -C Libft/ all

clean:
	@rm -rf $(OBJS)
#@rm -rf $(LIBMLX)/build
	@$(MAKE) -C Libft/ clean

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, #libmlx