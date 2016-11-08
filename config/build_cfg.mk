NAME = rtv1
TYPE = prog

MODULES = src mcpu
#CFLAGS = -Wall -Wextra -Werror -g
CFLAGS = -Wall -Wextra -Werror -flto -Ofast -march=native -mtune=native -ffinite-math-only -funsafe-math-optimizations -fno-math-errno  -ffast-math
LFLAGS = $(CFLAGS) -lm
INCLUDE_DIRS = $(PKG_DIR)/include
DEPS = libft xmlx

OUTPUT = $(NAME)

ifneq ($(filter mcpu,$(MODULES)),)
LFLAGS += -lpthread
endif
