# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/03 22:00:53 by dlaurent          #+#    #+#              #
#    Updated: 2018/09/03 19:14:47 by dlaurent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: 		all clean fclean re

NAME 		= 	minishell

CC 			=	gcc
CFLAGS		= 	-g3 -Wall -Wextra -Werror -I$(INC_DIR)

SRC_DIR 	=	./src/
SRC			=	minishell.c													\
				errors/malloc.c												\
				errors/path.c												\
				errors/term.c												\
				reading/cursor.c											\
				reading/read.c												\
				reading/signals.c											\
				structures/binaries/delete.c								\
				structures/binaries/hash.c									\
				structures/binaries/initialize.c							\
				structures/binaries/insert.c								\
				structures/binaries/new.c									\
				structures/binaries/search.c								\
				structures/environment/delete.c								\
				structures/environment/hash.c								\
				structures/environment/initialize.c							\
				structures/environment/insert.c								\
				structures/environment/new.c								\
				structures/environment/search.c								\
				structures/shell/delete.c									\
				structures/shell/new.c										\
				structures/read/delete.c									\
				structures/read/new.c										\
				structures/term/delete.c									\
				structures/term/new.c										\

#				functions/redirect.c										\
#				functions/cd/cd.c											\
#				functions/echo/echo.c										\
#				functions/env/env.c											\
#				functions/exit/exit											\
#				functions/setenv/setenv										\
#				functions/unsetenv/unsetenv									\
#				structures/commands/										\



SRCS		=	$(addprefix $(SRC_DIR), $(SRC_ALL))

OBJ_DIR 	=	./obj/
OBJ		 	=	$(SRC:.c=.o)
OBJS		=	$(addprefix $(OBJ_DIR), $(OBJ))

INC_DIR 	=	./include/
INC 		=	minishell.h
INCS 		=	$(addprefix $(INC_DIR), $(INC))

all:	 		minishell

minishell:		$(OBJ_DIR) $(OBJS)
				@make -C libft/
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L libft/ -lft -lcurses

$(OBJ_DIR)%.o: 	$(SRC_DIR)%.c $(INCS)
				$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
				@mkdir -p $(OBJ_DIR)
				@mkdir -p $(OBJ_DIR)/errors
				@mkdir -p $(OBJ_DIR)/functions
				@mkdir -p $(OBJ_DIR)/functions/cd
				@mkdir -p $(OBJ_DIR)/functions/echo
				@mkdir -p $(OBJ_DIR)/functions/env
				@mkdir -p $(OBJ_DIR)/functions/exit
				@mkdir -p $(OBJ_DIR)/functions/setenv
				@mkdir -p $(OBJ_DIR)/functions/unsetenv
				@mkdir -p $(OBJ_DIR)/reading
				@mkdir -p $(OBJ_DIR)/structures
				@mkdir -p $(OBJ_DIR)/structures/binaries
				@mkdir -p $(OBJ_DIR)/structures/commands
				@mkdir -p $(OBJ_DIR)/structures/environment
				@mkdir -p $(OBJ_DIR)/structures/read
				@mkdir -p $(OBJ_DIR)/structures/shell
				@mkdir -p $(OBJ_DIR)/structures/term

clean:
				@make clean -C libft/
				@rm -f $(OBJS)
				@rm -rf $(OBJ_DIR)

fclean: 		clean
				@make fclean -C libft/
				@rm -f $(NAME)

re: 			fclean all
