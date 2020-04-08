NAME = minishell

CFLAGS = -std=c99 -Wall -Werror -Wextra

INCLUDE = lib/libft/include/

LIBFT_PATH = lib/libft/
LIBFT_FLAG = -lft
LIBFT_NAME = libft.a
LIBFT = $(addprefix $(LIBFT_PATH), $(LIBFT_NAME))

SRC =
SRCDIR = src/

_SRC = \
	builtin/cd.c \
	builtin/echo.c \
	builtin/env.c \
	builtin/exit.c \
	builtin/setenv.c \
	builtin/unsetenv.c \
	exec.c \
	main.c \
	prompt.c
SRC += $(addprefix $(SRCDIR), $(_SRC))

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDE) -o $@ -c $<

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT_PATH) CC="$(CC)" CFLAGS="$(CFLAGS)"
	$(CC) $^ -L $(LIBFT_PATH) $(LIBFT_FLAG) -o $@

all: $(NAME)

clean:
	$(MAKE) -C $(LIBFT_PATH) $@
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) $@
	$(RM) $(NAME)

re: fclean all

docker-build:
	docker build -t $(NAME) .

docker-run:
	docker run --interactive --tty --rm $(NAME)

.PHONY: all clean fclean re docker-build docker-run
