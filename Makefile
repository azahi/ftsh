# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdeathlo <jdeathlo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/03 19:48:19 by jdeathlo          #+#    #+#              #
#    Updated: 2020/02/24 21:06:46 by jdeathlo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -std=c99 -Wall -Werror -Wextra

INCLUDE = lib/libft/include/

LIBFT_PATH = lib/libft
LIBFT_FLAG = -lft

SRC =
SRCDIR = src/

_SRC = \
	builtin/cd.c \
	builtin/echo.c \
	builtin/env.c \
	builtin/exit.c \
	builtin/setenv.c \
	builtin/unsetenv.c \
	env.c \
	exec.c \
	main.c \
	prompt.c
SRC += $(addprefix $(SRCDIR), $(_SRC))

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDE) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $^ -L $(LIBFT_PATH) $(LIBFT_FLAG) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

docker-build:
	docker build -t $(NAME) .

docker-run:
	docker run --interactive --tty --rm $(NAME)

.PHONY: all clean fclean re docker-build docker-run
