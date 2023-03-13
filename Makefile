# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 12:03:11 by znichola          #+#    #+#              #
#    Updated: 2023/03/13 14:28:17 by skoulen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT

CC	= gcc
CFLAGS	= -Wall -Wextra -Werror

ifdef DEBUG
CFLAGS	+= -g3 -fsanitize=address
else
ifdef DEBUGL
CFLAGS += -g3
endif
endif

PARSING_FILES = parse
FILES	= main $(addprefix parsing/, $(PARSING_FILES))
HEADERS = includes/minirt.h

OBJS_PATH = objs/
SRCS_PATH = srcs/
INCS_PATH = -Iincludes/. -Imlx -Ilibft/includes -Ignl
LIBS_PATH = -Lmlx -Llibft -Lgnl
LIBS      = -lmlx -lft -lgnl
FRAMEWORK = -framework OpenGL -framework AppKit

SRCS	= $(addprefix $(SRCS_PATH), $(addsuffix .c, $(FILES)))
OBJS	= $(addprefix $(OBJS_PATH), $(addsuffix .o, $(FILES)))

MLX = mlx/libmlx.a
LIBFT = libft/libft.a
GNL = gnl/libgnl.a

all : $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCS_PATH) -c $< -o $@

$(NAME): $(HEADERS) $(MLX) $(LIBFT) $(GNL) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS_PATH) $(LIBS) $(FRAMEWORK) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:
	$(RM) $(NAME)

$(MLX):
	@$(MAKE) -C mlx

$(LIBFT):
	@$(MAKE) -C libft

$(GNL):
	@$(MAKE) -C gnl

re: clean all

# tests below

tests/parsing_test: $(filter-out objs/main.o, $(OBJS)) tests/parsing_test.c
	$(CC) $(CFLAGS) -o $@ -Iincludes $^