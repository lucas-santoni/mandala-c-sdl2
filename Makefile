## Makefile for Mandalas
## By Geographer
## Greetz to Epitech Coding Club

CC	= gcc

CFLAGS	+= -W -Werror -Wall -Wextra -pedantic
CFLAGS	+= -O3 -g3

LDFLAGS	+= -lSDL2 -lm

SRCS	= mandala.c

OBJS	= $(SRCS:.c=.o)

RM	= rm -f

NAME	= mandala

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
