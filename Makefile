# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akovalev <akovalev@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/29 17:34:25 by akovalev          #+#    #+#              #
#    Updated: 2024/07/15 16:41:41 by akovalev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= cub3d
CFLAGS	:= -Wunreachable-code -Ofast #-Wall -Wextra -Werror 
LIBMLX	:= ./MLX42

HEADERS	:= -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -pthread -lm -L/Users/$(USER)/.brew/Cellar/glfw/3.3.8/lib -lglfw

#SRCS	:=	ray_tracing_test_01.c
SRCS	:=	parsing.c
#SRCS	:=	image_to_screen_test.c
			
OBJS	:= ${SRCS:.c=.o} Libft/libft.a

all: $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS) libmlx
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

Libft/libft.a:
	@$(MAKE) -C Libft/ all

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@$(MAKE) -C Libft/ clean

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx