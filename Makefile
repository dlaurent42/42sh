# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/03 22:00:53 by dlaurent          #+#    #+#              #
#    Updated: 2018/09/24 00:10:51 by dhojt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: 		all clean fclean re

NAME 		= 	shell

CC 			=	gcc
CFLAGS		= 	-g3 -Wall -Wextra -Werror -I$(INC_DIR)

SRC_DIR 	=	./src/
SRC			=	shell.c														\
				debug.c														\
				errors/malloc.c												\
				errors/path.c												\
				functions/redirect.c										\
				structures/binaries/delete.c								\
				structures/binaries/execute_fetch.c							\
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
				structures/read/delete.c									\
				structures/read/new.c										\
				structures/shell/delete.c									\
				structures/shell/new.c										\
				structures/shell/set_prompt.c								\
				structures/shell/set_prompt.folder.c						\
				structures/shell/set_prompt.git.c							\
				terminal/autocompletion/autocompletion.c					\
				terminal/autocompletion/sort/sort.c \
				terminal/autocompletion/sort/sort_alpha.c \
				terminal/autocompletion/issuance/issuance.c \
				terminal/autocompletion/issuance/move_up.c \
				terminal/autocompletion/issuance/move_down.c \
				terminal/autocompletion/issuance/move_left.c \
				terminal/autocompletion/issuance/move_right.c \
				terminal/autocompletion/issuance/get_attributes.c \
				terminal/autocompletion/issuance/do_ls.c \
				terminal/autocompletion/issuance/path.c \
				terminal/autocompletion/issuance/loop_dirs.c \
				terminal/autocompletion/issuance/loop_valid_dir.c \
				terminal/autocompletion/issuance/calc_len_file_name.c \
				terminal/autocompletion/issuance/is_executeable.c \
				terminal/autocompletion/issuance/do_file_admin.c \
				terminal/autocompletion/issuance/calculate_number_of_columns.c \
				terminal/autocompletion/issuance/replace_buffer.c \
				terminal/autocompletion/display/display.c \
				terminal/autocompletion/display/get_diff.c \
				terminal/autocompletion/display/file_name.c \
				terminal/autocompletion/display/print_spaces.c \
				terminal/autocompletion/auto_completion/auto_completion.c \
				terminal/autocompletion/auto_completion/free_frame.c \
				terminal/autocompletion/auto_completion/error_exit.c \
				terminal/autocompletion/auto_completion/get_args.c \
				terminal/autocompletion/auto_completion/create_args.c \
				terminal/autocompletion/auto_completion/free_args.c \
				terminal/cursor/move_end.c									\
				terminal/cursor/move_home.c									\
				terminal/cursor/move_left.c									\
				terminal/cursor/move_right.c								\
				terminal/cursor/move_xy.c									\
				terminal/cursor/move_prev_word.c							\
				terminal/cursor/move_next_word.c							\
				terminal/cursor/utils.c										\
				terminal/printer/buffer.c									\
				terminal/printer/prompt.c									\
				terminal/reader/delete.c									\
				terminal/reader/read.c										\
				terminal/signals/catch.c									\
				terminal/signals/resize.c		

				
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
INC 		=	shell.h
INCS 		=	$(addprefix $(INC_DIR), $(INC))

all:	 		shell

shell:			$(OBJ_DIR) $(OBJS)
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
				@mkdir -p $(OBJ_DIR)/structures
				@mkdir -p $(OBJ_DIR)/structures/binaries
				@mkdir -p $(OBJ_DIR)/structures/commands
				@mkdir -p $(OBJ_DIR)/structures/environment
				@mkdir -p $(OBJ_DIR)/structures/read
				@mkdir -p $(OBJ_DIR)/structures/shell
				@mkdir -p $(OBJ_DIR)/structures/term
				@mkdir -p $(OBJ_DIR)/terminal
				@mkdir -p $(OBJ_DIR)/terminal/autocompletion
				@mkdir -p $(OBJ_DIR)/terminal/autocompletion/sort
				@mkdir -p $(OBJ_DIR)/terminal/autocompletion/issuance
				@mkdir -p $(OBJ_DIR)/terminal/autocompletion/display
				@mkdir -p $(OBJ_DIR)/terminal/autocompletion/auto_completion
				@mkdir -p $(OBJ_DIR)/terminal/cursor
				@mkdir -p $(OBJ_DIR)/terminal/printer
				@mkdir -p $(OBJ_DIR)/terminal/reader
				@mkdir -p $(OBJ_DIR)/terminal/signals

clean:
				@make clean -C libft/
				@rm -f $(OBJS)
				@rm -rf $(OBJ_DIR)

fclean: 		clean
				@make fclean -C libft/
				@rm -f $(NAME)

re: 			fclean all
