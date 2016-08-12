NAME = rtv1
TYPE = prog

MODULES = src
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -Wall -Wextra -Werror -g -lm
INCLUDE_DIRS = ./include
DEPS = libft xmlx

OUTPUT = $(NAME)
