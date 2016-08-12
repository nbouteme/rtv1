ifeq ($(RUNDIR),)
	RUNDIR := $(CURDIR)
else
	SUBFOLDERS += $(shell find $(RUNDIR) -maxdepth 1 -type d ! -path $(RUNDIR) ! -path $(RUNDIR)/config | grep -v '/\.')
endif

load $(RUNDIR)/config/ext_make.so(setup)

SHELL = /bin/bash
SYSTEM = $(shell uname)
TERM_WIDTH := $(get-term-info WIDTH)

define redout
$(shell printf "\033[0;31m%s\033[0m" "$(strip $1)")
endef

define blueout
$(shell printf "\033[0;34m%s\033[0m" "$(strip $1)")
endef

define greenout
$(shell printf "\033[0;32m%s\033[0m" "$(strip $1)")
endef

src_from_modules = $(shell find $1 -maxdepth 1 -type f | grep -v '/\.' | grep '.c$$')
nsrc_from_modules = $(shell find $1 -maxdepth 1 -type f | grep -v '/\.' | grep '.c$$' | wc -l)
file_exist = $(shell test -e $1 && echo "exist")
eq = $(and $(findstring $(1),$(2)),$(findstring $(2),$(1)))
get_val_in_file =	$(if $(call file_exist,$1),\
						$(shell cat $1  | sed -n "s/$2.=.\(.*\)/\1/p"))

BUILD_CFG := $(shell ls ./config/build_cfg.mk 2> /dev/null)
LINK_CFG := $(shell ls ./config/link_cfg.mk 2> /dev/null)
SUBFOLDERS := $(shell find `pwd` -maxdepth 1 -type d ! -path `pwd` ! -path `pwd`/config ! -path `pwd`/build  | grep -v '/\.')

CURDIR := $(shell pwd)

ifeq ($(BUILD_CFG),)
$(error $(call redout,Missing build config file))
endif

ifeq ($(LINK_CFG),)
$(error $(call redout,Missing link config file))
endif

PKG_DIR = .

include $(BUILD_CFG)

ifeq ($(NAME),)
$(error $(call redout,Missing project name))
endif

ifeq ($(OUTPUT),)
$(error $(call redout,Missing project output))
endif

ifeq ($(MODULES),)
$(error $(call redout,Missing project modules))
endif

ifeq ($(TYPE),)
$(error $(call redout,Missing project type))
endif

CUR_NAME := $(NAME)
CUR_INCLUDE_DIRS := $(INCLUDE_DIRS)
CUR_OPTS := $(OPTS)
CUR_TYPE := $(TYPE)
CUR_DEPS := $(DEPS)
CUR_OUTPUT := $(OUTPUT)

CUR_MODULES := $(shell find $(MODULES) -mindepth 1 -type d)

LFLAGS_ACC := $(LFLAGS)
CFLAGS_ACC := $(addprefix -I,$(INCLUDE_DIRS)) $(CFLAGS)

S_LFLAGS_ACC := $(LFLAGS_$(SYSTEM))
S_CFLAGS_ACC := $(CFLAGS_$(SYSTEM))

S_FLAGS_ACC := $(SFLAGS_$(SYSTEM))

all: $(CUR_OUTPUT)

define GEN_DEP_RULE
$1:
	make -C $2 RUNDIR=$(RUNDIR)
endef

$(foreach dep,$(CUR_DEPS), \
	$(foreach dir,$(SUBFOLDERS), \
		$(eval CURNAME:=$(call get_val_in_file,$(dir)/config/build_cfg.mk,NAME))\
		$(if $(call file_exist,$(dir)/config/build_cfg.mk),\
			$(eval \
				CURNAME=$(call get_val_in_file,$(dir)/config/build_cfg.mk,NAME)\
				$(if $(call eq,$(CURNAME),$(dep)), \
					$(if $(shell make -q -C $(dir) RUNDIR=$(RUNDIR) &> /dev/null || echo "not_updat_ed"),\
						$(shello make --no-print-directory -C $(dir) RUNDIR=$(RUNDIR)))\
					$(eval $(dep)_FOUND=true) \
					$(eval PKG_DIR=$(dir)) \
					$(eval include $(dir)/config/link_cfg.mk)\
					$(eval LFLAGS_ACC += $(LFLAGS))\
					$(eval CFLAGS_ACC += $(CFLAGS))\
					$(eval SFLAGS_ACC += $(SFLAGS_$(SYSTEM)))\
					$(eval S_LFLAGS_ACC += $(LFLAGS_$(SYSTEM)))\
					$(eval S_CFLAGS_ACC += $(CFLAGS_$(SYSTEM)))\
					$(eval include $(dir)/config/build_cfg.mk)\
					$(eval DEP_ACC += $(OUTPUT))\
					$(eval $(call GEN_DEP_RULE,$(OUTPUT),$(dir))))\
			)\
		)\
	)\
	$(if $($(dep)_FOUND),,$(error Dependency $(dep) not found.))\
)

SRCS := $(call src_from_modules, $(CUR_MODULES))
NSRCS := $(call nsrc_from_modules, $(CUR_MODULES))
OBJS := $(SRCS:.c=.o)
BUILD_DEPS = build

$(init-pb $(NSRCS),$(TERM_WIDTH))

build:
	$(info $(call blueout,Building temporary build directory hierachy...))
	@mkdir -p build

define BUILD_DIR_RULE
build/$1: build
	@mkdir -p build/$1

build/$1/%.o: $1/%.c
	$$(gen-pb $$^)
	@$(CC) $$(CFLAGS_ACC) $$(S_CFLAGS_ACC) -c $$^ -o $$@ $$(SFLAGS_ACC)
endef

$(foreach mod,$(CUR_MODULES),\
	$(eval BUILD_DEPS += build/$(mod))\
	$(eval $(call BUILD_DIR_RULE,$(mod)))\
)

$(print-head $(CUR_OUTPUT),$(TERM_WIDTH))

tail:
	$(print-tail $(TERM_WIDTH))

$(CUR_OUTPUT): $(BUILD_DEPS) $(DEP_ACC) $(addprefix build/,$(OBJS)) | tail
	@printf "\e[34mLinking %s..." $(CUR_OUTPUT)
ifeq ($(CUR_TYPE),prog)
	@$(CC) $(addprefix build/,$(OBJS)) -o $(CUR_OUTPUT) $(LFLAGS_ACC) $(S_LFLAGS_ACC) $(SFLAGS_ACC)
else
	@ld -r $(addprefix build/,$(OBJS)) -o $(OUTPUT)
endif
	@printf "\e[32m✓\e[0m\n"

.PHONY: clean fclean re all

clean: | tail
	@/bin/rm -rf $(addprefix build/,$(OBJS))

fclean: clean | tail
	@/bin/rm -rf $(CUR_OUTPUT) build

re: fclean all
