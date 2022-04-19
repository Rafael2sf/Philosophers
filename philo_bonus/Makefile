# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 10:56:28 by rafernan          #+#    #+#              #
#    Updated: 2022/03/25 15:16:22 by rafernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################ PROGRAM ################

NAME	=		philosophers

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

_OBJ	=		./obj/

############### COMPILER ################

CC		=		cc
CFLAGS	=		-Wall -Werror -Wextra 
CFLAGS	+=		-g -fsanitize=thread

################ FILES ##################

SRCS	=		\
				init.c		\
				utils.c		\
				wait.c		\
				routine.c	\
				log.c		\
				monitor.c	\
				main.c

OBJS	=		$(patsubst $(_SRC)%.c,$(_OBJ)%.o,$(SRCS))
LIBS	=		-pthread

################ RULES ##################

all: $(NAME)

$(_OBJ)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(_OBJ) $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $(NAME)

############## STRUCTURE ################

$(_OBJ):
	$(MKD) $@

################### CLEAN ###############

clean:
	$(RMV) -r $(_OBJ)

fclean: clean
	$(RMV) $(NAME)

re: fclean all

.PHONY: all clean fclean re
