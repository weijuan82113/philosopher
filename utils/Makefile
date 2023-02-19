# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/19 17:37:37 by wchen             #+#    #+#              #
#    Updated: 2023/02/20 00:38:52 by wchen            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libutils.a

# CC CFLAG
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -MMD -MP

# DIRS
OBJ_DIR			= ./objs
SRC_DIR			= ./srcs

# SRCS
UTILS_SRC		= ft_atoll.c
SRCS			= $(addprefix $(SRC_DIR)/, $(UTILS_SRC))

# OBJS
OBJ				= $(SRCS:%.c=%.o)
OBJS			= $(addprefix $(OBJ_DIR)/, $(OBJ))

# DEPS
DEPS			= $(SRCS:%.c=%.d)

# INCLUDES
INCLUDES_DIR	= ./includes
IFLAGS			= $(addprefix -I, $(INCLUDES_DIR))

# RULES

all : $(NAME)

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o	:%.c
	@mkdir -p $$(dirname $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PYONY : all clean fclean re

-include	$(DEPS)
