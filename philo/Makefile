# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 10:56:28 by rafernan          #+#    #+#              #
#    Updated: 2021/12/16 16:28:53 by rafernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################ PROGRAM ################

NAME	=		what

################ TERMINAL ###############

RMV		=		rm -f
MKD		=		mkdir
PRT		=		printf
MKE		=		make
CPY		=		cp

################# COLORS ################

--GRN	=		\033[32m
--RED	=		\033[31m
--WHT	=		\033[39m

################# DIRS ##################

_SRC	=		src/
_OBJ	=		obj/
_LIB	=		libs/
_BIN	=		./

############### COMPILER ################

CC		=		gcc
CF		=		-g -Wall -Werror -Wextra

################ FILES ##################

SRCS	=		$(_SRC)main.c
OBJS	=		$(patsubst $(_SRC)%.c,$(_OBJ)%.o,$(SRCS))
DEPS	=		libft.a libph.a
LIBS	=		-lft -lph

################ RULES ##################

all: deps $(NAME)

$(_OBJ)%.o: $(_SRC)%.c
	$(CC) $(CF) -c $< -o $@

$(_BIN)$(NAME): deps $(OBJS)
	$(CC) $(CF) $(LIBS) $(OBJS) -o $@ -L $(_LIB)

################ DEPS ###################

deps: $(DEPS)

libft.a:
	$(MKE) libft.a -C src/libft/

libph.a:
	$(MKE) libph.a -C src/libph/

############## STRUCTURE ################

$(_OBJ):
	$(MKD) $(_OBJ)

$(_LIB):
	$(MKD) $(_LIB)

$(_SRC):
	$(MKD) $(_SRC)

$(_BIN):
	$(MKD) $(_BIN)

################### CLEAN ###############

clean:
	$(RMV) -r $(_OBJ) $(_LIB)

fclean: clean
	$(RMV) -r $(NAME)

re: fclean all

rebonus: fclean bonus

.PHONY: all deps clean fclean re rebonus
