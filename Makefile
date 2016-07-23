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

SUPL = -lm -Lminilibx -lmlx

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
SUPL += -lX11 -lXext
else
SUPL += -framework OpenGL -framework AppKit
endif

SUPL += -lm

##################
include mkgen.mk #
##################
