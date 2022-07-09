# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgoncalv <lgoncalv@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 12:05:54 by lgoncalv          #+#    #+#              #
#    Updated: 2022/07/09 11:35:12 by lgoncalv         ###   ########.fr        #
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
PRINTF_DIR		= $(LIBRARIES_DIR)/printf

# FLAGS
C_FLAGS			= -Wall -Wextra -Werror
LIBFT_FLAGS		= -L $(LIBFT_DIR) -lft
PRINTF_FLAGS		= -L $(PRINTF_DIR) -lprintf
INCLUDES		= -I $(INCLUDES_DIR) -I $(LIBFT_DIR) -I $(PRINTF_DIR)

# COMMANDS
RM				= /bin/rm -fr

# NAMES
NAME			= pipex
LIBFT		= $(LIBFT_DIR)/libft.a

# SOURCES
SOURCES			= main.c\
				error_handler.c
SOURCES			:= $(addprefix $(SOURCES_DIR)/,$(SOURCES))

# OBJECTS
OBJECTS			= $(subst $(SOURCES_DIR),$(OBJECTS_DIR),$(SOURCES:%.c=%.o))

# COMPILE RULE
$(OBJECTS_DIR)/%.o : $(SOURCES_DIR)/%.c
	mkdir -p $(OBJECTS_DIR)
	$(CC) $(C_FLAGS) $(INCLUDES) -c $< -o $@

# RULES
all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(C_FLAGS) $(INCLUDES) $(OBJECTS) $(LIBFT_FLAGS) -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJECTS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

run_clean: fclean
	clear
	$(MAKE) all
	./pipex

libft: $(LIBcleaFT)

.PHONY: all clean fcelan re run_clean
