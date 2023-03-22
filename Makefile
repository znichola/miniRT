# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 12:03:11 by znichola          #+#    #+#              #
#    Updated: 2023/03/22 18:29:07 by skoulen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT

CC	= gcc
CFLAGS	= -Wall -Wextra
# CFLAGS 	+= -Werror

ifdef OPTI
CFLAGS	+= -O$(OPTI)
else
ifdef SYMB
CFLAGS += -g3
else
ifdef DEBUG
CFLAGS	+= -g3 -fsanitize=address
endif
endif
endif

UI_FILES		:= destroy_window mouse_hooks keyboard_hooks
RENDER_FILES	:= render_frame put_pixel render_sphere trpg_colour light \
					lerp_colour the_moon multithread render_colour render_world
MATHS_FILES		:= vector matrix poi_sphere
UTILS_FILES		:= debug_prints singletons
PARSING_FILES	:= parse parse_utils parse_scalar parse_properties parse_objects1 parse_objects2 scene parse_error scene_add_object

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
	$(RM) libminirt.a

$(MLX):
	@$(MAKE) -C mlx

$(LIBFT):
	@$(MAKE) -C libft

$(GNL):
	@$(MAKE) -C gnl

#create an archive containing all functions
#useful for testing purposes
archive: $(OBJS) $(MLX) $(GNL) $(LIBFT)
	mkdir -p tmp1 tmp2 tmp3
	cd tmp1; ar -x ../$(MLX)
	cd tmp2; ar -x ../$(GNL)
	cd tmp3; ar -x ../$(LIBFT)
	ar -rcs libminirt.a tmp1/* tmp2/* tmp3/* $(OBJS)
	rm -rf tmp1 tmp2 tmp3

re: clean all
