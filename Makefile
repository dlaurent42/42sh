.PHONY: 		all clean fclean re

NAME 		= 	42sh

CC 			=	gcc
CFLAGS		= 	-Wall -Wextra -Werror -I$(INC_DIR) -I./libdyn/incs

SRC_DIR 	=	./src/
SRC			=	shell.c														\
				errors/execution.c											\
				errors/import_export.c										\
				errors/malloc.c												\
				errors/parsing.c											\
				errors/path.c												\
				errors/subshell.c											\
				terminal/signals/stop_acquisition.c							\
				functions/ast/build_list.c									\
				functions/ast/get_tree_token_type.c							\
				functions/ast/build_token_tree.c							\
				functions/ast/exec.c										\
				functions/ast/reorganiser.c									\
				functions/ast/reorganise_command.c							\
				functions/ast/reorganise_and_or.c							\
				functions/ast/reorganise_squashing.c						\
				functions/ast/arg_merge.c									\
				functions/ast/operators/semicolon.c							\
				functions/ast/operators/conditions.c						\
				functions/ast/operators/pipe.c								\
				functions/ast/operators/left_redirection.c					\
				functions/ast/operators/right_redirection.c					\
				functions/ast/operators/heredoc.c							\
				functions/ast/operators/file_descriptor.c					\
				functions/ast/operators/file_descriptor_utils.c				\
				functions/backtick/execute.c								\
				functions/backtick/prep.c									\
				functions/backtick/capture.c								\
				functions/builtins/list_of_builtins.c						\
				functions/builtins/alias/add.c								\
				functions/builtins/alias/alias.c							\
				functions/builtins/alias/error.c							\
				functions/builtins/cd/cd.c									\
				functions/builtins/cd/dispatch.c							\
				functions/builtins/cd/error.c								\
				functions/builtins/cd/follow.c								\
				functions/builtins/cd/follow_parser.c						\
				functions/builtins/cd/nofollow.c							\
				functions/builtins/cd/options.c								\
				functions/builtins/cd/utils.c								\
				functions/builtins/echo/echo.c								\
				functions/builtins/env/env.c								\
				functions/builtins/env/error.c								\
				functions/builtins/env/mode.display.c						\
				functions/builtins/env/mode.exec.c							\
				functions/builtins/exit/exit.c								\
				functions/builtins/export/add.c								\
				functions/builtins/export/error.c							\
				functions/builtins/export/export.c							\
				functions/builtins/history/error.c							\
				functions/builtins/history/history.c						\
				functions/builtins/history/options.c						\
				functions/builtins/history/options.c.c						\
				functions/builtins/history/options.d.c						\
				functions/builtins/history/options.sp.c						\
				functions/builtins/history/options.warn.c					\
				functions/builtins/history/print.c							\
				functions/builtins/jobcontrol/jobs.c						\
				functions/builtins/jobcontrol/jobs_bg.c						\
				functions/builtins/jobcontrol/jobs_fg.c						\
				functions/builtins/jobcontrol/jobs_launch.c					\
				functions/builtins/read/assign.c							\
				functions/builtins/read/error.c								\
				functions/builtins/read/options.arguments.c					\
				functions/builtins/read/options.c							\
				functions/builtins/read/read.c								\
				functions/builtins/read/reading_loop.c						\
				functions/builtins/read/variables.c							\
				functions/builtins/setenv/add.c								\
				functions/builtins/setenv/error.c							\
				functions/builtins/setenv/setenv.c							\
				functions/builtins/unalias/error.c							\
				functions/builtins/unalias/remove.c							\
				functions/builtins/unalias/unalias.c						\
				functions/builtins/unset/error.c							\
				functions/builtins/unset/remove.c							\
				functions/builtins/unset/unset.c							\
				functions/builtins/unsetenv/error.c							\
				functions/builtins/unsetenv/remove.c						\
				functions/builtins/unsetenv/unsetenv.c						\
				functions/builtins/utils/equal_position.c					\
				functions/builtins/utils/is_option_str.c					\
				functions/builtins/utils/is_binary.c						\
				functions/builtins/utils/parse_quotes.c						\
				functions/builtins/utils/path_from_filename.c				\
				functions/check/aliases.c									\
				functions/check/check.c										\
				functions/check/lexer.c										\
				functions/jobs/background.c									\
				functions/jobs/continue.c									\
				functions/jobs/display.c									\
				functions/jobs/execute.c									\
				functions/jobs/foreground.c									\
				functions/jobs/launch.c										\
				functions/jobs/message.c									\
				functions/jobs/notification.c								\
				functions/jobs/utils.c										\
				functions/jobs/wait.c										\
				functions/process/launch.c									\
				functions/process/status.c									\
				functions/lexer/aliases/aliases.c							\
				functions/lexer/backtick/lexer.c							\
				functions/lexer/backtick/splice_point.c						\
				functions/lexer/dollar/dollar.c								\
				functions/lexer/glob/glob.c									\
				functions/lexer/glob/lexer.c								\
				functions/lexer/glob/cbraces/cbraces.c						\
				functions/lexer/glob/cbraces/check.c						\
				functions/lexer/glob/cbraces/dot.c							\
				functions/lexer/glob/cbraces/dot.replace.c					\
				functions/lexer/glob/cbraces/list.c							\
				functions/lexer/glob/cbraces/start_and_stop.c				\
				functions/lexer/glob/pattern/pattern.c						\
				functions/lexer/glob/pattern/parse/expand_ranges.c			\
				functions/lexer/glob/pattern/parse/remove_wildcards.c		\
				functions/lexer/glob/pattern/paths/add.c					\
				functions/lexer/glob/pattern/paths/check.c					\
				functions/lexer/glob/utils/match.c							\
				functions/lexer/glob/utils/range.c							\
				functions/lexer/glob/utils/cbraces_strsplit.c				\
				functions/lexer/glob/utils/pattern_strsplit.c				\
				functions/lexer/glob/utils/conditions.c						\
				functions/lexer/heredoc/add.c								\
				functions/lexer/heredoc/all_closed.c						\
				functions/lexer/heredoc/delete.c							\
				functions/lexer/heredoc/get_next.c							\
				functions/lexer/heredoc/heredoc.c							\
				functions/lexer/heredoc/init.c								\
				functions/lexer/heredoc/orga.c								\
				functions/lexer/heredoc/update.c							\
				functions/lexer/tilde/tilde.c								\
				functions/lexer/tokenize/delete.c							\
				functions/lexer/tokenize/fill.c								\
				functions/lexer/tokenize/lexic_singletone.c					\
				functions/lexer/tokenize/subshell.c							\
				functions/lexer/tokenize/token_add.c						\
				functions/lexer/tokenize/token_backquote.c					\
				functions/lexer/tokenize/token_doublequote.c				\
				functions/lexer/tokenize/token_search.c						\
				functions/lexer/tokenize/token_singlequote.c				\
				functions/lexer/tokenize/token_merge.c						\
				functions/lexer/utils/backslash.c							\
				functions/lexer/utils/inject.c								\
				functions/lexer/utils/is_empty.c							\
				functions/lexer/utils/is_escape.c							\
				functions/lexer/utils/is_new_command.c						\
				functions/lexer/utils/is_quote.c							\
				functions/lexer/utils/need_escape.c							\
				functions/lexer/utils/repatriate.c							\
				functions/lexer/utils/strcountif_esc.c						\
				functions/lexer/utils/strsplit.c							\
				functions/lexer/utils/strsplit_ws.c							\
				functions/lexer/utils/useless_quotes.c						\
				functions/parser/build.c									\
				functions/parser/is_not_builtin.c							\
				functions/parser/parser.c									\
				functions/parser/test_path.c								\
				functions/run/execute.c										\
				functions/run/prepare.c										\
				functions/run/run.c											\
				functions/run/run.lexer.c									\
				functions/run/run.tree.c									\
				functions/subshell/subshell.c								\
				functions/subshell/execute.c								\
				structures/ast/add.c										\
				structures/ast/new.c										\
				structures/ast/clean.c										\
				structures/ast/copy.c										\
				structures/ast/last.c										\
				structures/binaries/delete.c								\
				structures/binaries/hash.c									\
				structures/binaries/initialize.c							\
				structures/binaries/insert.c								\
				structures/binaries/new.c									\
				structures/binaries/update.c								\
				structures/binaries/search.c								\
				structures/binaries/gen_list_for_auto_comp.c				\
				structures/commands/add.c									\
				structures/commands/append_from.c							\
				structures/commands/append_to.c								\
				structures/commands/delete.c								\
				structures/commands/export_to.c								\
				structures/commands/export.c								\
				structures/commands/import_from.c							\
				structures/commands/import.c								\
				structures/environment/autocompletion.c						\
				structures/environment/copy.c								\
				structures/environment/display.c							\
				structures/environment/delete.c								\
				structures/environment/hash.c								\
				structures/environment/initialize.c							\
				structures/environment/insert.c								\
				structures/environment/key_check.c							\
				structures/environment/local_to_public.c					\
				structures/environment/new.c								\
				structures/environment/search.c								\
				structures/environment/utils.c								\
				structures/environment/ini/config.c							\
				structures/environment/ini/histfile.c						\
				structures/environment/ini/home.c							\
				structures/environment/ini/ini.c							\
				structures/environment/ini/ppid.c							\
				structures/environment/ini/ps.c								\
				structures/environment/ini/pwd.c							\
				structures/environment/ini/shell.c							\
				structures/environment/ini/shlvl.c							\
				structures/environment/ini/specials.c						\
				structures/environment/ini/term.c							\
				structures/gnl/delete.c										\
				structures/gnl/gnl.c										\
				structures/jobs/add.c										\
				structures/jobs/new.c										\
				structures/jobs/destroy.c									\
				structures/jobs/get_max_id.c								\
				structures/jobs/delete.c									\
				structures/jobs/completed.c									\
				structures/jobs/stopped.c									\
				structures/jobs/get_by_id.c									\
				structures/read/delete.c									\
				structures/read/new.c										\
				structures/shell/delete.c									\
				structures/shell/import_config.c							\
				structures/shell/new.c										\
				structures/shell/set_prompt.c								\
				structures/shell/set_prompt.folder.c						\
				structures/shell/set_prompt.git.c							\
				structures/shell/termios.c									\
				structures/shell/exec.c										\
				structures/process/process_add.c							\
				structures/process/process_destroy.c						\
				structures/process/process_destroy_all.c					\
				structures/process/process_destroy_pid.c					\
				structures/process/process_display.c						\
				structures/process/process_get.c							\
				structures/process/process_get_pid.c						\
				structures/process/process_new.c							\
				terminal/autocompletion/auto_completion/auto_completion.c	\
				terminal/autocompletion/auto_completion/free_ac.c			\
				terminal/autocompletion/auto_completion/get_obj.c			\
				terminal/autocompletion/auto_completion/create_obj.c		\
				terminal/autocompletion/auto_completion/free_obj.c			\
				terminal/autocompletion/auto_completion/utils.c				\
				terminal/autocompletion/display/display.c					\
				terminal/autocompletion/display/clear_selection_screen.c	\
				terminal/autocompletion/display/file_name.c					\
				terminal/autocompletion/display/print_spaces.c				\
				terminal/autocompletion/issuance/path.c						\
				terminal/autocompletion/issuance/do_ls.c					\
				terminal/autocompletion/issuance/move_up.c					\
				terminal/autocompletion/issuance/issuance.c					\
				terminal/autocompletion/issuance/move_down.c				\
				terminal/autocompletion/issuance/move_left.c				\
				terminal/autocompletion/issuance/move_right.c				\
				terminal/autocompletion/issuance/merge_objs.c				\
				terminal/autocompletion/issuance/show_screen.c				\
				terminal/autocompletion/issuance/do_file_admin.c			\
				terminal/autocompletion/issuance/get_attributes.c			\
				terminal/autocompletion/issuance/is_executeable.c			\
				terminal/autocompletion/issuance/read_dispatcher.c			\
				terminal/autocompletion/issuance/do_special_modes.c			\
				terminal/autocompletion/issuance/get_escaped_string.c		\
				terminal/autocompletion/issuance/calc_len_file_name.c		\
				terminal/autocompletion/issuance/calculate_number_of_columns.c\
				terminal/autocompletion/env/env.c							\
				terminal/autocompletion/history/history.c					\
				terminal/autocompletion/history/hist_double.c				\
				terminal/autocompletion/history/hist_question.c				\
				terminal/autocompletion/history/hist_name.c					\
				terminal/autocompletion/history/hist_sed.c					\
				terminal/autocompletion/history/hist_number.c				\
				terminal/autocompletion/history/hist_new_prompt.c			\
				terminal/autocompletion/sort/sort.c							\
				terminal/autocompletion/glob/glob.c							\
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
				terminal/signals/default.c									\
				terminal/signals/resize.c

SRCS		=	$(addprefix $(SRC_DIR), $(SRC_ALL))

OBJ_DIR 	=	./obj/
OBJ		 	=	$(SRC:.c=.o)
OBJS		=	$(addprefix $(OBJ_DIR), $(OBJ))

INC_DIR 	=	./include/
INC 		=	shell.h														\
				constants.h													\
				prototypes.h												\
				structures.h

INCS 		=	$(addprefix $(INC_DIR), $(INC))

all:	 		$(NAME)

$(NAME):		$(OBJ_DIR) $(OBJS)
				@make -C libdyn/
				@make -C libft/
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L libft/ -L libdyn/ -lft -ldyn -lcurses

$(OBJ_DIR)%.o: 	$(SRC_DIR)%.c $(INCS)
				$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
				@mkdir -p $(OBJ_DIR)
				@mkdir -p $(OBJ_DIR)/errors
				@mkdir -p $(OBJ_DIR)/functions
				@mkdir -p $(OBJ_DIR)/functions/ast
				@mkdir -p $(OBJ_DIR)/functions/ast/operators
				@mkdir -p $(OBJ_DIR)/functions/backtick
				@mkdir -p $(OBJ_DIR)/functions/builtins
				@mkdir -p $(OBJ_DIR)/functions/builtins/alias
				@mkdir -p $(OBJ_DIR)/functions/builtins/cd
				@mkdir -p $(OBJ_DIR)/functions/builtins/echo
				@mkdir -p $(OBJ_DIR)/functions/builtins/env
				@mkdir -p $(OBJ_DIR)/functions/builtins/exit
				@mkdir -p $(OBJ_DIR)/functions/builtins/export
				@mkdir -p $(OBJ_DIR)/functions/builtins/history
				@mkdir -p $(OBJ_DIR)/functions/builtins/jobcontrol
				@mkdir -p $(OBJ_DIR)/functions/builtins/read
				@mkdir -p $(OBJ_DIR)/functions/builtins/setenv
				@mkdir -p $(OBJ_DIR)/functions/builtins/unalias
				@mkdir -p $(OBJ_DIR)/functions/builtins/unset
				@mkdir -p $(OBJ_DIR)/functions/builtins/unsetenv
				@mkdir -p $(OBJ_DIR)/functions/builtins/utils
				@mkdir -p $(OBJ_DIR)/functions/check
				@mkdir -p $(OBJ_DIR)/functions/jobs
				@mkdir -p $(OBJ_DIR)/functions/lexer
				@mkdir -p $(OBJ_DIR)/functions/lexer/aliases
				@mkdir -p $(OBJ_DIR)/functions/lexer/backtick
				@mkdir -p $(OBJ_DIR)/functions/lexer/dollar
				@mkdir -p $(OBJ_DIR)/functions/lexer/glob
				@mkdir -p $(OBJ_DIR)/functions/lexer/glob/cbraces
				@mkdir -p $(OBJ_DIR)/functions/lexer/glob/pattern
				@mkdir -p $(OBJ_DIR)/functions/lexer/glob/pattern/parse
				@mkdir -p $(OBJ_DIR)/functions/lexer/glob/pattern/paths
				@mkdir -p $(OBJ_DIR)/functions/lexer/glob/utils
				@mkdir -p $(OBJ_DIR)/functions/lexer/heredoc
				@mkdir -p $(OBJ_DIR)/functions/lexer/tilde
				@mkdir -p $(OBJ_DIR)/functions/lexer/tokenize
				@mkdir -p $(OBJ_DIR)/functions/lexer/utils
				@mkdir -p $(OBJ_DIR)/functions/parser
				@mkdir -p $(OBJ_DIR)/functions/process
				@mkdir -p $(OBJ_DIR)/functions/run
				@mkdir -p $(OBJ_DIR)/functions/subshell
				@mkdir -p $(OBJ_DIR)/structures
				@mkdir -p $(OBJ_DIR)/structures/ast
				@mkdir -p $(OBJ_DIR)/structures/binaries
				@mkdir -p $(OBJ_DIR)/structures/commands
				@mkdir -p $(OBJ_DIR)/structures/environment
				@mkdir -p $(OBJ_DIR)/structures/environment/ini
				@mkdir -p $(OBJ_DIR)/structures/gnl
				@mkdir -p $(OBJ_DIR)/structures/jobs
				@mkdir -p $(OBJ_DIR)/structures/read
				@mkdir -p $(OBJ_DIR)/structures/shell
				@mkdir -p $(OBJ_DIR)/structures/process
				@mkdir -p $(OBJ_DIR)/terminal
				@mkdir -p $(OBJ_DIR)/terminal/autocompletion
				@mkdir -p $(OBJ_DIR)/terminal/autocompletion/env
				@mkdir -p $(OBJ_DIR)/terminal/autocompletion/glob
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
				@make clean -C libdyn/
				@rm -f $(OBJS)
				@rm -rf $(OBJ_DIR)

fclean: 		clean
				@make fclean -C libft/
				@make fclean -C libdyn/
				@rm -f $(NAME)

re: 			fclean all
