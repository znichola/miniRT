# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 12:03:11 by znichola          #+#    #+#              #
#    Updated: 2023/03/13 14:33:12 by skoulen          ###   ########.fr        #
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
SRC_FILES     = main $(addprefix parsing/, $(PARSING_FILES))
HEADER_FILES  = minirt

OBJS_PATH = objs/
SRCS_PATH = srcs/
LIBS_PATH = -Lmlx -Llibft -Lgnl
LIBS      = -lmlx -lft -lgnl
HEADR_PATH	= includes/
INCS_PATH = -I$(HEADR_PATH). -Imlx -Ilibft/includes -Ignl
FRAMEWORK = -framework OpenGL -framework AppKit

SRCS	= $(addprefix $(SRCS_PATH), $(addsuffix .c, $(SRC_FILES)))
OBJS	= $(addprefix $(OBJS_PATH), $(addsuffix .o, $(SRC_FILES)))
HEADERS	= $(addprefix $(HEADR_PATH), $(addsuffix .h, $(HEADER_FILES)))

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