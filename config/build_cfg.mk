NAME = rtv1
TYPE = prog

MODULES = src mcpu gpu
CFLAGS = -Wall -Wextra -Werror -g
#CFLAGS = -Wall -Wextra -Werror -flto -Ofast -march=native -mtune=native -ffinite-math-only -funsafe-math-optimizations -fno-math-errno  -ffast-math
LFLAGS = $(CFLAGS) -lm
INCLUDE_DIRS = $(PKG_DIR)/include
DEPS = libft xmlx

OUTPUT = $(NAME)

ifneq ($(filter mcpu,$(MODULES)),)
LFLAGS += -lpthread
endif

ifneq ($(filter gpu,$(MODULES)),)

#TODO: check system
CUDA_LIBS = /opt/cuda/lib64

gpu_CC := nvcc
gpu_CFLAGS = -g --std=c++11 -ccbin g++ -m64 -gencode arch=compute_20,code=sm_20 -gencode arch=compute_30,code=sm_30 $(addprefix -I,$(INCLUDE_DIRS_ACC))
gpu_EXT := .cu
LFLAGS += -L$(CUDA_LIBS) -lcudart -lstdc++
endif
