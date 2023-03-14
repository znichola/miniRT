# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 12:03:11 by znichola          #+#    #+#              #
#    Updated: 2023/03/14 12:29:25 by znichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT

CC	= gcc
CFLAGS	= -Wall -Wextra -Werror

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
RENDER_FILES	:= render_frame put_pixel render_sphere trpg_colour
MATHS_FILES		:= vector
UTILS_FILES		:= debug_prints

HEADER_FILES	:= colour control_enums defines maths render structs ui utils

FILES			:= main $(addprefix ui/, $(UI_FILES)) $(addprefix render/, $(RENDER_FILES)) \
					$(addprefix maths/, $(MATHS_FILES)) $(addprefix utils/, $(UTILS_FILES))
HEADER_FILES	:= minirt $(addprefix minirt_, $(HEADER_FILES)) $(addprefix libft/includes, $(LIBFT_HEADERS))

OBJS_PATH	= objs/
SRCS_PATH	= srcs/
HEADR_PATH	= includes/

INCS_PATH = -I$(HEADR_PATH). -Imlx -Ilibft/includes
LIBS_PATH = -Lmlx -Llibft
LIBS      = -lmlx -lft
FRAMEWORK = -framework OpenGL -framework AppKit

SRCS	= $(addprefix $(SRCS_PATH), $(addsuffix .c, $(FILES)))
OBJS	= $(addprefix $(OBJS_PATH), $(addsuffix .o, $(FILES)))
HEADERS	= $(addprefix $(HEADR_PATH), $(addsuffix .h, $(HEADER_FILES)))

MLX = mlx/libmlx.a
LIBFT = libft/libft.a

all : $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCS_PATH) -c $< -o $@

$(NAME): $(HEADERS) $(MLX) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS_PATH) $(LIBS) $(FRAMEWORK) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:
	$(RM) $(NAME)

$(MLX):
	@$(MAKE) -C mlx

$(LIBFT):
	@$(MAKE) -C libft

re: clean all
