# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/03 22:00:53 by dlaurent          #+#    #+#              #
#    Updated: 2018/10/07 22:53:00 by dlaurent         ###   ########.fr        #
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
				functions/list_of_builtins.c								\
				functions/cd/cd.c											\
				functions/cd/error.c										\
				functions/cd/follow.c										\
				functions/cd/follow_parser.c								\
				functions/cd/nofollow.c										\
				functions/cd/options.c										\
				functions/echo/echo.c										\
				functions/env/env.c											\
				functions/env/error.c										\
				functions/env/mode.display.c								\
				functions/env/mode.exec.c									\
				functions/env/parse.c										\
				functions/env/parse.actions.c								\
				functions/env/parse.prepare.c								\
				functions/exit/exit.c										\
				functions/history/history.c									\
				functions/setenv/add.c										\
				functions/setenv/error.c									\
				functions/setenv/parse.c									\
				functions/setenv/setenv.c									\
				functions/setenv/utils.c									\
				functions/unsetenv/errors.c									\
				functions/unsetenv/parse.c									\
				functions/unsetenv/remove.c									\
				functions/unsetenv/unsetenv.c								\
				functions/utils/has_option.c								\
				structures/binaries/delete.c								\
				structures/binaries/hash.c									\
				structures/binaries/initialize.c							\
				structures/binaries/insert.c								\
				structures/binaries/new.c									\
				structures/binaries/search.c								\
				structures/binaries/gen_list_for_auto_comp.c				\
				structures/commands/add.c									\
				structures/commands/delete.c								\
				structures/commands/execute_fetch.c							\
				structures/commands/export.c								\
				structures/commands/import.c								\
				structures/environment/copy.c								\
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
				terminal/autocompletion/sort/sort.c							\
				terminal/autocompletion/sort/sort_alpha.c					\
				terminal/autocompletion/issuance/issuance.c					\
				terminal/autocompletion/issuance/read_dispatcher.c			\
				terminal/autocompletion/issuance/move_up.c					\
				terminal/autocompletion/issuance/manage_buffer.c			\
				terminal/autocompletion/issuance/move_down.c				\
				terminal/autocompletion/issuance/move_left.c				\
				terminal/autocompletion/issuance/move_right.c				\
				terminal/autocompletion/issuance/get_attributes.c			\
				terminal/autocompletion/issuance/do_ls.c					\
				terminal/autocompletion/issuance/path.c						\
				terminal/autocompletion/issuance/show_screen.c				\
				terminal/autocompletion/issuance/calc_len_file_name.c		\
				terminal/autocompletion/issuance/is_executeable.c			\
				terminal/autocompletion/issuance/do_file_admin.c			\
				terminal/autocompletion/issuance/calculate_number_of_columns.c\
				terminal/autocompletion/display/display.c					\
				terminal/autocompletion/display/clear_selection_screen.c	\
				terminal/autocompletion/display/file_name.c					\
				terminal/autocompletion/display/print_spaces.c				\
				terminal/autocompletion/auto_completion/auto_completion.c	\
				terminal/autocompletion/auto_completion/free_frame.c		\
				terminal/autocompletion/auto_completion/get_args.c			\
				terminal/autocompletion/auto_completion/create_args.c		\
				terminal/autocompletion/auto_completion/free_args.c			\
				terminal/autocompletion/history/history.c					\
				terminal/cursor/move_down.c									\
				terminal/cursor/move_end.c									\
				terminal/cursor/move_home.c									\
				terminal/cursor/move_left.c									\
				terminal/cursor/move_right.c								\
				terminal/cursor/move_up.c									\
				terminal/cursor/move_xy.c									\
				terminal/cursor/move_prev_word.c							\
				terminal/cursor/move_next_word.c							\
				terminal/cursor/utils.c										\
				terminal/delete/delete_all.c								\
				terminal/delete/delete_char.c								\
				terminal/delete/delete_current_char.c						\
				terminal/delete/delete_left_word.c							\
				terminal/delete/delete_right_word.c							\
				terminal/delete/delete_from_home.c							\
				terminal/delete/delete_to_end.c								\
				terminal/history/browse/next.c								\
				terminal/history/browse/prev.c								\
				terminal/history/browse/comparison.c						\
				terminal/history/browse/freeze.c							\
				terminal/history/search/bufferize.c							\
				terminal/history/search/cursor.c							\
				terminal/history/search/freeze.c							\
				terminal/history/search/initialize.c						\
				terminal/history/search/print.c								\
				terminal/history/search/read.c								\
				terminal/history/search/search.c							\
				terminal/multilines/initialize.c							\
				terminal/multilines/close.c									\
				terminal/print/buffer.c										\
				terminal/print/command.c									\
				terminal/print/prompt.c										\
				terminal/print/selection.c									\
				terminal/print/welcome.c									\
				terminal/read/dispatcher.c									\
				terminal/read/read.c										\
				terminal/read/utils.c										\
				terminal/select/cut.c										\
				terminal/select/copy.c										\
				terminal/select/paste.c										\
				terminal/select/select_down.c								\
				terminal/select/select_left.c								\
				terminal/select/select_left_word.c							\
				terminal/select/select_right.c								\
				terminal/select/select_right_word.c							\
				terminal/select/select_to_end.c								\
				terminal/select/select_to_home.c							\
				terminal/select/select_up.c									\
				terminal/select/unselect.c									\
				terminal/select/utils.c										\
				terminal/signals/catch.c									\
				terminal/signals/resize.c

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
				@mkdir -p $(OBJ_DIR)/functions/history
				@mkdir -p $(OBJ_DIR)/functions/setenv
				@mkdir -p $(OBJ_DIR)/functions/unsetenv
				@mkdir -p $(OBJ_DIR)/functions/utils
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
				@mkdir -p $(OBJ_DIR)/terminal/autocompletion/history
				@mkdir -p $(OBJ_DIR)/terminal/autocompletion/issuance
				@mkdir -p $(OBJ_DIR)/terminal/autocompletion/display
				@mkdir -p $(OBJ_DIR)/terminal/autocompletion/auto_completion
				@mkdir -p $(OBJ_DIR)/terminal/cursor
				@mkdir -p $(OBJ_DIR)/terminal/delete
				@mkdir -p $(OBJ_DIR)/terminal/history
				@mkdir -p $(OBJ_DIR)/terminal/history/browse
				@mkdir -p $(OBJ_DIR)/terminal/history/search
				@mkdir -p $(OBJ_DIR)/terminal/multilines
				@mkdir -p $(OBJ_DIR)/terminal/print
				@mkdir -p $(OBJ_DIR)/terminal/read
				@mkdir -p $(OBJ_DIR)/terminal/select
				@mkdir -p $(OBJ_DIR)/terminal/signals

clean:
				@make clean -C libft/
				@rm -f $(OBJS)
				@rm -rf $(OBJ_DIR)

fclean: 		clean
				@make fclean -C libft/
				@rm -f $(NAME)

re: 			fclean all
