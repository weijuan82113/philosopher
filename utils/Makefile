# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/19 17:37:37 by wchen             #+#    #+#              #
#    Updated: 2023/02/19 18:17:21 by wchen            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= utils.a

# CC CFLAG
CC				= CC
CFLAG			= -Wall -Wextra -Werror -MMD -MP

# DIRS
OBJ_DIR			= ./objs
SRC_DIR			= ./srcs

# SRCS
UTILS_SRCS		= ft_atoll.c
SRCS			= $(addprefix $(SRC_DIR)/, $(UTILS_SRCS))

# OBJS
OBJ				= $(SRCS:%.c=%.o)
OBJS			= $(addprefix $(OBJ_DIR)/, $(OBJ))

# DEPS
DEPS			= $(SRCS:%.c=%.d)

# INCLUDES
INCLUDES_DIR	= ./includes
IFLAGS			= $(addprefix -I, $(INCLUDES_DIR))

# RULES
$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)
	#$(CC $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o	:%.c
	@mkdir -p $$(dirname $@)
	$(CC) $(CFLAG) $(IFLAG) -c $< -o $@

all : $(NAME)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PYONY : all clean fclean re

-include	$(DEPS)
