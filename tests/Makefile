NAME = unit-tests
CC = gcc
CFLAGS = -Wall -Wextra

INCS_PATH = -I. -I../includes/ -I../mlx -I../gnl -I../libft/includes -I$(CHECK)/include
LIBS_PATH = -L.. -L$(CHECK)/lib
LIBS = -lminirt -lcheck

ARCHIVE = ../libminirt.a

TESTS_PARSING = test_parse_float test_parse_position test_parse_color test_parse_objects test_parse

TESTS_MATHS = test_poi_sphere

FILES = main $(addprefix parsing/, $(TESTS_PARSING)) $(addprefix maths/, $(TESTS_MATHS))

SRCS = $(addsuffix .c, $(FILES))
OBJS = $(addsuffix .o, $(FILES))

%.o: %.c
	$(CC) $(CFLAGS) -c $(INCS_PATH) -o $@ $<

all: $(NAME)

$(NAME): update-archive $(ARCHIVE) $(OBJS)
	$(CC) $(CFLAGS) $(LIBS_PATH) $(LIBS) -o $@ $(OBJS)

clean:
	rm -f $(OBJS)
	make clean -C ..

fclean: clean
	rm -f $(NAME)
	make fclean -C ..

re: fclean all

.PHONY: all fclean clean re update-archive

update-archive:
	make archive -C ..