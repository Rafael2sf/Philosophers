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

NAME	=		philosophers

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

_OBJ	=		./obj/

################### COMPILER ############

CC		=		cc
CFLAGS	=		-Wall -Werror -Wextra
#CFLAGS	+=		-fsanitize=thread

################### FILES ###############

SRCS	=		\
				init.c \
				utils.c \
				clear.c \
				thread.c \
				wait.c \
				log.c \
				fork.c \
				main.c

OBJS	=		$(patsubst %.c,$(_OBJ)%.o,$(SRCS))
LIBS	=		-lpthread

################### RULES ###############

all: $(NAME)

$(_OBJ)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(_OBJ) $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $(NAME)

################### STRUCTURE ###########

$(_OBJ):
	$(MKD) $@

################### CLEAN ###############

clean:
	$(RMV) -r $(_OBJ)

fclean: clean
	$(RMV) $(NAME)

re: fclean all

.PHONY: all clean fclean re
