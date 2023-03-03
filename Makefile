# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/19 23:32:07 by wchen             #+#    #+#              #
#    Updated: 2023/03/02 00:09:50 by wchen            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# COMPILE FLAGS
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -MMD -MP

SRC_DIR	= ./srcs
SRC		= main.c \
		  init_philo.c \
		  print_return.c \
		  time.c \
		  judge_die.c \
		  free_all.c \
		  judge_state.c \
		  print_state.c \
		  do_action.c \

SRCS = $(addprefix $(SRC_DIR)/, $(SRC))

OBJ_DIR	= ./objs
OBJ		= $(SRCS:%.c=%.o)
OBJS	= $(addprefix $(OBJ_DIR)/, $(OBJ))

# DEPS
DEPS	= $(OBJS:%.o:%.d)

# LIBFT
LIBUTILS_DIR	= ./utils
LIBUTILS_NAME	= libutils.a
LIBUTILS		= $(addprefix $(LIBUTILS_DIR), $(LIBUTILS_NAME))

# LFLAG
LIBS_DIR	= $(LIBUTILS_DIR)
LFLAGS		= $(addprefix -L, $(LIBS_DIR)) -lutils

# IFLAGS
INCLUDES_DIR = ./includes
INCLUDES	 = $(INCLUDES_DIR)
IFLAGS		 = $(addprefix -I, $(INCLUDES))

# RULES
all		: $(NAME)

$(NAME) : $(OBJS)
	@make -C $(LIBUTILS_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) $(OBJS) -o $@

$(OBJ_DIR)/%.o :%.c
	@mkdir -p $$(dirname $@)
	$(CC) $(CFLAG) $(IFLAGS) -c $< -o $@

clean 	:
	@make clean -C $(LIBUTILS_DIR)
	rm -rf $(OBJ_DIR)

fclean	: clean
	rm -rf $(NAME)
	@make fclean -C $(LIBUTILS_DIR)

re		: fclean all

.PHONY	: all clean fclean re $(DEPS)

-include	$(DEPS)
