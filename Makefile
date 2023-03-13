# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 12:03:11 by znichola          #+#    #+#              #
#    Updated: 2023/03/13 14:15:18 by znichola         ###   ########.fr        #
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

SRC_FILES		= main
HEADER_FILES	= minirt

OBJS_PATH	= objs/
SRCS_PATH	= srcs/
HEADR_PATH	= includes/

INCS_PATH = -I$(HEADR_PATH). -Imlx -Ilibft/includes
LIBS_PATH = -Lmlx -Llibft
LIBS      = -lmlx -lft
FRAMEWORK = -framework OpenGL -framework AppKit

SRCS	= $(addprefix $(SRCS_PATH), $(addsuffix .c, $(SRC_FILES)))
OBJS	= $(addprefix $(OBJS_PATH), $(addsuffix .o, $(SRC_FILES)))
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
