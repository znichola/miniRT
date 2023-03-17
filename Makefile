# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 12:03:11 by znichola          #+#    #+#              #
#    Updated: 2023/03/17 12:51:01 by znichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT

CC	= gcc
CFLAGS	= -Wall -Wextra
# CFLAGS 	+= -Werror

ifdef OPTI
CFLAGS	+= -O3
else
ifdef SYMB
CFLAGS += -g3
else
ifdef DEBUG
CFLAGS	+= -g3 -fsanitize=address
endif
endif
endif

UI_FILES		:= destroy_window mouse_movement_track mouse_on_click mouse_on_release keyboard_press
RENDER_FILES	:= render_frame put_pixel render_sphere trpg_colour light lerp_colour the_moon
MATHS_FILES		:= vector
UTILS_FILES		:= debug_prints
PARSING_FILES := parse

HEADER_FILES	:= colour_defs control_enums defines maths render structs ui utils

FILES			:= main $(addprefix ui/, $(UI_FILES)) $(addprefix render/, $(RENDER_FILES)) \
					$(addprefix maths/, $(MATHS_FILES)) $(addprefix utils/, $(UTILS_FILES))\
          $(addprefix parsing/, $(PARSING_FILES))
HEADER_FILES	:= minirt $(addprefix minirt_, $(HEADER_FILES)) $(addprefix libft/includes, $(LIBFT_HEADERS))


OBJS_PATH = objs/
SRCS_PATH = srcs/
LIBS_PATH = -Lmlx -Llibft -Lgnl
LIBS      = -lmlx -lft -lgnl
HEADR_PATH	= includes/
INCS_PATH = -I$(HEADR_PATH). -Imlx -Ilibft/includes -Ignl
FRAMEWORK = -framework OpenGL -framework AppKit

SRCS	= $(addprefix $(SRCS_PATH), $(addsuffix .c, $(FILES)))
OBJS	= $(addprefix $(OBJS_PATH), $(addsuffix .o, $(FILES)))
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

fclean: clean
	$(RM) $(NAME)

$(MLX):
	@$(MAKE) -C mlx

$(LIBFT):
	@$(MAKE) -C libft

$(GNL):
	@$(MAKE) -C gnl

re: clean all

# tests below

OBJS_TO_TEST = $(filter-out objs/main.o, $(OBJS))

# parsing
PARSING_TEST_FILES = $(addprefix tests/parsing/files/, valid1.rt)
PARSING_TEST_EXEC = tests/parsing/parsing_test
PARSING_TEST_SRC = tests/parsing/parsing_test.c

$(PARSING_TEST_EXEC): $(GNL) $(MLX) $(LIBFT) $(OBJS_TO_TEST) $(PARSING_TEST_SRC)
	$(CC) $(CFLAGS) -o $@ $(INCS_PATH) $(LIBS_PATH) $(LIBS) $^

run_parsing_tests: $(PARSING_TEST_EXEC)
	@for filename in $(PARSING_TEST_FILES); do\
		$(PARSING_TEST_EXEC) $$filename;\
	done;
