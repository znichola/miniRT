# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 12:03:11 by znichola          #+#    #+#              #
#    Updated: 2023/03/13 12:16:53 by znichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= $(addsuffix .c, $(SNAME))
OBJ		= $(SRC:%.c=%.o)

NAME	= miniRT

CC	= gcc
CFLAGS	= -Wall -Wextra
# CFLAGS	+= -Werror

ifdef DEBUG
CFLAGS	+= -g3 -fsanitize=address
else
ifdef DEBUGL
CFLAGS += -g3
endif
endif

FILES	= main

# FILES	= $(addprefix turtle/, $(FILE_NAMES))

OBJS_PATH = objs/
SRCS_PATH = srcs/
INCS_PATH = -Iincludes/.

SRCS	= $(addprefix $(SRCS_PATH), $(addsuffix .c, $(FILES)))
OBJS	= $(addprefix $(OBJS_PATH), $(addsuffix .o, $(FILES)))

all : $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCS_PATH) -Imlx -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:
	$(RM) $(NAME)

mlx :
	$(MAKE) -C mlx

re: clean all
