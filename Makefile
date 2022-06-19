# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgoncalv <lgoncalv@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 12:05:54 by lgoncalv          #+#    #+#              #
#    Updated: 2022/06/19 12:24:12 by lgoncalv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILER
CC				= gcc

# PATHS
SOURCES_DIR		= ./sources
OBJECTS_DIR		= ./objects
INCLUDES_DIR	= ./includes
LIBRARIES_DIR	= ./libraries
LIBFT_DIR		= $(LIBRARIES_DIR)/libft

# FLAGS
C_FLAGS			= -Wall -Wextra -Werror
LIBFT_FLAGS		= -L $(LIBFT_DIR) -lft
INCLUDES		= -I $(INCLUDES_DIR) -I $(LIBFT_DIR)

# COMMANDS
RM				= /bin/rm -fr

# NAMES
NAMES			= pipex
LIBFT_DIR		= $(LIBFT_DIR)/libft.a

# SOURCES
SOURCES			= main.c
SOURCES			:= $(addprefix $(SOURCES_DIR)/,$(SOURCES))

# OBJECTS
OBJECTS			= $(subst $(SOURCES_DIR),$(OBJECTS_DIR),$(SOURCES:%.c=%.o))

# COMPILE RULE
$(OBJECTS_DIR)/%.o : $(SOURCES_DIR)/%.C
	mkdir -p $(OBJECTS_DIR)
	$(CC) $(C_FLAGS) $(INCLUDES) -c $< -o $@

# RULES
all: $(NAME)

$(NAME) : $(LIBFT) $(OBJECTS)
	$(CC) $(C_FLAGS) $(INCLUDES) $(OBJECTS) $(LIBFT_FLAGS) -o $@

$(LIBFT) :
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(LIBFT) clean
	$(RM) $(OBJECTS)

fclean: clean
	$(LIBFT) fclean
	$(RM) $(NAME)

re: fclean all

run_clean: fclean
	clear
	all

.PHONY: all clean fcelan re run_clean