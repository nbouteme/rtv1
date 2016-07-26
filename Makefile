#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/23 11:08:14 by nbouteme          #+#    #+#              #
#    Updated: 2016/07/23 04:49:28 by nbouteme         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = rtv1
OPTS = -g

SUPL = -lm -ldl -lglfw -Lxmlx -lxmlx

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
SUPL += -lGL
else
SUPL += -framework OpenGL -framework AppKit
endif

##################
include mkgen.mk #
##################
