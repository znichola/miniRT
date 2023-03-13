# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 12:03:11 by znichola          #+#    #+#              #
#    Updated: 2023/03/13 18:53:39 by znichola         ###   ########.fr        #
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

UI_FILES		:= destroy_window mouse_movement_track mouse_on_click mouse_on_release keyboard_press
RENDER_FILES	:= render_frame put_pixel render_sphere
MATHS_FILES		:= vector

HEADER_FILES	:= structs defines render control_enums colour maths

FILES			:= main $(addprefix ui/, $(UI_FILES)) $(addprefix render/, $(RENDER_FILES)) $(addprefix maths/, $(MATHS_FILES))
HEADER_FILES	:= minirt $(addprefix minirt_, $(HEADER_FILES))

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
