# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 11:34:36 by rafernan          #+#    #+#              #
#    Updated: 2021/12/14 14:12:00 by rafernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

############# STATIC LIBRARY ############

NAME	=		libph.a

################### TERMINAL ############

RMV		=		rm -f
MKD		=		mkdir
PRT		=		printf
MKE		=		make
CPY		=		cp

################### COLORS ##############

--GRN	=		\033[32m
--RED	=		\033[31m
--WHT	=		\033[39m

################### DIRS ################

_SRC	=
_OBJ	=		../../obj/
_LIB	=		../../libs/

################### COMPILER ############

CC		=		gcc
AR		=		ar rcs
CF		=		-g -Wall -Werror -Wextra

################### FILES ###############

SRCS_	=		\
				init.c \
				utils.c \
				clear.c \
				thread.c \
				wait.c \
				log.c

SRCS	=		$(addprefix $(_SRC), $(SRCS_))
OBJS	=		$(patsubst $(_SRC)%.c,$(_OBJ)%.o,$(SRCS))

################### RULES ###############

all: $(NAME)

$(_OBJ)%.o: $(_SRC)%.c
	$(CC) $(CF) -c $< -o $@

$(NAME): $(_LIB) $(_LIB)$(NAME)
$(_LIB)$(NAME): $(_OBJ) $(OBJS)
	$(AR) $@ $(OBJS)

################### STRUCTURE ###########

$(_OBJ):
	$(MKD) $@

$(_LIB):
	$(MKD) $@

$(_SRC):
	$(MKD) $@

################### CLEAN ###############

clean:
	$(RMV) $(OBJS)

fclean: clean
	$(RMV) $(_LIB)$(NAME)

re: fclean all

.PHONY: all clean fclean re