# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 12:03:11 by znichola          #+#    #+#              #
#    Updated: 2023/05/13 13:28:13 by znichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT

CC	= gcc
CFLAGS	= -Wall -Wextra -Werror

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

UI_FILES		:= destroy_window mouse_hooks keyboard_hooks keybinds render_ui selection make_selection
RENDER_FILES	:=  put_pixel \
					lerp_colour the_moon render_world \
					pix_shader
MATHS_FILES		:= vector matrix poi_sphere poi_plane colour poi_cylinder poi_cone
UTILS_FILES		:= debug_prints singletons trgb
PRIMITIVES_FILES	:= sphere plane cylinder cone

PARSING_FILES	:= parser parse_utils parse_scalar parse_properties scene scene_add_object parse_obj_ambiant parse_obj_camera parse_obj_cylinder parse_obj_light parse_obj_plane parse_obj_sphere tokenize validate grammar_check parse_obj_cone
GETTERS_FILES	:= getters getters2 getters3
THREADS_FILES	:= multithread give_and_release mutexes partial_render

HEADER_FILES	:= colour_defs control_enums defines maths render structs ui utils

FILES			:= main texture $(addprefix ui/, $(UI_FILES)) $(addprefix render/, $(RENDER_FILES)) \
					$(addprefix maths/, $(MATHS_FILES)) $(addprefix utils/, $(UTILS_FILES))\
					$(addprefix parsing/, $(PARSING_FILES)) $(addprefix primitives/, $(PRIMITIVES_FILES))\
					$(addprefix getters/, $(GETTERS_FILES))\
					$(addprefix threads/, $(THREADS_FILES))
HEADER_FILES	:= minirt $(addprefix minirt_, $(HEADER_FILES)) $(addprefix libft/includes, $(LIBFT_HEADERS))

OBJS_PATH = objs/
SRCS_PATH = srcs/
LIBS_PATH = -Lmlx -Llibft -Lgnl
LIBS      = -lmlx -lft -lgnl
# with threads
LIBS     += -pthread

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
