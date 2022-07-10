# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgoncalv <lgoncalv@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 12:05:54 by lgoncalv          #+#    #+#              #
#    Updated: 2022/07/09 21:13:36 by lgoncalv         ###   ########.fr        #
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
PRINTF_FLAGS	= -L $(PRINTF_DIR) -lprintf
INCLUDES		= -I $(INCLUDES_DIR) -I $(LIBFT_DIR) -I $(LIBFT_DIR)/includes -I $(PRINTF_DIR)

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
	@mkdir -p $(OBJECTS_DIR)
	@$(CC) $(C_FLAGS) $(INCLUDES) -c $< -o $@

# RULES
all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@$(CC) $(C_FLAGS) $(INCLUDES) $(OBJECTS) $(LIBFT_FLAGS) -o $@
	@echo "[PIPEX] Program [$(NAME)] created!"

$(LIBFT):
	@git submodule update --remote
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@$(RM) infile outfile
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) $(OBJECTS)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)

re: fclean all

run_clean: fclean
	clear
	$(MAKE) all
	./pipex "infile" "ls -l" "wc -l" "outfile"

simple_run: fclean $(LIBFT)
	clear
	gcc sources/*.c $(INCLUDES) $(LIBFT_FLAGS) -o pipex && ./pipex "file1" "ls -l" "wc -l" "file2"

$(ARG):
	echo "./pipex" "infile" "ls -l" "wc -l" "outfile"
	

.PHONY: all clean fcelan re run_clean

valgrind:
	valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes --tool=memcheck ./pipex "infile" "ls -l" "wc -l" "outfile"

test:
	$(MAKE) -C pipex-tester


# how do I update te branch my submodule is pointing to? 
# currently, if I use git submodule update it will bring the branch back to the first commit
# i have to use git submodule update --remote