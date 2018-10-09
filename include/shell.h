/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:39:05 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/09 10:29:22 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "../libft/include/libft.h"
# include "auto_completion.h"
# include "key_strokes.h"
# include <curses.h>
# include <dirent.h>
# include <signal.h>
# include <term.h>
# include <termios.h>
# include <time.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>

# ifndef ARG_MAX
#  define ARG_MAX 		262144
# endif

# define VERIF_KEY		"j3Y72kqqTtENSVPoufEpmMB0sbQsr9Tt"

# define ENV_MAX_SIZE	999
# define ENV_PRIME_1	3
# define ENV_PRIME_2	13

# define BIN_MAX_SIZE	9999
# define BIN_PRIME_1	3
# define BIN_PRIME_2	13

# define LINE_SIZE		8

# define SEARCH_LEN		3

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct termios	t_termios;
typedef struct winsize	t_winsize;

typedef struct			s_bin_obj
{
	char				*name;
	char				*path;
	t_stat				stats;
}						t_bin_obj;

typedef struct			s_bin_item
{
	char				*key;
	t_bin_obj			*value;
}						t_bin_item;

typedef struct			s_bin_auto
{
	char				*name;
	struct s_bin_auto	*next;
}						t_bin_auto;

typedef struct			s_bin
{
	size_t				size;
	size_t				count;
	t_bin_item			del;
	t_bin_item			**items;
	t_bin_auto			*bin_auto;
}						t_bin;

typedef struct			s_env_item
{
	char				*key;
	char				*value;
}						t_env_item;

typedef struct			s_env
{
	char				*environment[ENV_MAX_SIZE + 1];
	size_t				size;
	size_t				count;
	t_env_item			del;
	t_env_item			**items;
}						t_env;

typedef struct			s_cmd
{
	char				content[ARG_MAX + 1];
	int					unicode_len;
	int					display_len;
	unsigned int		id;
	struct s_cmd		*last;
	struct s_cmd		*prev;
	struct s_cmd		*next;
}						t_cmd;

typedef struct			s_cursor
{
	int					x;
	int					y;
	int					abs_pos;
	int					rel_pos;
}						t_cursor;

typedef struct			s_buffer
{
	int					unicode_len;
	int					display_len;
	int					ushift;
	int					dshift;
	char				content[ARG_MAX + 1];
	char				stored[ARG_MAX + 1];
	t_cmd				*cmd;
}						t_buffer;

typedef struct			s_prompt
{
	int					rows;
	int					len;
	int					len_mod;
	char				*content;
	char				*location;
	char				last_exec_succeed;
}						t_prompt;

typedef struct			s_read
{
	char				line[LINE_SIZE];
	char				unicode_bytes_left;
}						t_read;

typedef struct			s_window
{
	short				width;
	short				height;
}						t_window;

typedef struct			s_modes
{
	unsigned char		auto_completion	: 1;
	unsigned char		esc				: 1;
	unsigned char		display			: 1;
	unsigned char		select			: 1;
	unsigned char		browse			: 1;
	unsigned char		search			: 1;
	unsigned char		others			: 2;
	unsigned int		multiline;
}						t_modes;

typedef struct			s_select
{
	int					start_rel;
	int					start_abs;
	int					stop;
	char				*content;
}						t_select;

typedef struct			s_search
{
	int					len;
	int					old_len;
	char				content[ARG_MAX + 1];
	t_cmd				*match;
}						t_search;

typedef struct			s_shell
{
	t_ac				*ac;
	char				*hist;
	t_bin				*bin;
	t_cmd				*cmd;
	t_env				*env;
	t_read				*read;
	t_modes				modes;
	t_cursor			cursor;
	t_prompt			prompt;
	t_window			window;
	t_buffer			buffer;
	t_search			search;
	t_select			selection;
	t_termios			*termios;
}						t_shell;

t_shell					*g_sh;

void					sh_debug(t_shell *sh, char *msg, char *str);

/*
** errors
*/
void					error_malloc_sh(t_shell *sh);
void					error_malloc_env(t_shell *sh, t_env *e, char *name);
void					error_malloc_bin(t_shell *sh, t_bin *b, char *name);
void					error_malloc_reader(t_shell *sh, char *name);
void					error_no_path_var(t_shell *sh);

/*
** functions
*/
void					sh_command_run(t_shell *sh);
void					sh_add_builtins_to_auto_comp(t_shell *sh, t_bin *bin);

/*
** functions - cd
*/
int						sh_cd_remove_troll(char *s);
int						sh_cd_options(char **argv, bool *opt_l, bool *opt_p);
char					sh_cd(t_shell *sh, char **argv);
char					sh_cd_error(char *value, char *path, int err_id);
char					sh_cd_follow(t_shell *sh, char *value, char dash);
char					sh_cd_nofollow(t_shell *sh, char *v, char *p, char d);
char					*sh_cd_parse_path(char *s);
char					*sh_cd_remove_last_slash(char *param);

/*
** functions - echo
*/
char					sh_echo(t_shell *sh, char **argv);

/*
** functions - env
*/
char					sh_env(t_shell *sh, char **argv);
char					sh_env_string(char *arg, char **string);
char					sh_env_path(char *arg, char **path);
char					sh_env_unset(t_env *env, char *arg, bool verbose);
char					sh_env_empty(t_env *env, bool verbose);
bool					sh_env_has_verbose(char **argv);
char					sh_env_error(t_env *env, char *s1, char *s2, int id);
char					sh_env_exec(t_env *env, char *path, char **arr, bool v);
char					sh_env_display(t_shell *s, t_env *e, char **a, bool v);
char					sh_env_parse(t_env *e, char **p, char **s, char **av);
char					*sh_env_prepare_u(int *j, int *i, char **argv);
char					sh_env_prepare_s(char **s, int *j, int *i, char **argv);
char					sh_env_prepare_p(char **p, int *j, int *i, char **argv);

/*
** functions - exit
*/
char					sh_exit(t_shell *sh, char **argv);

/*
** functions - history
*/
char					sh_history(t_shell *sh, char **argv);
char					sh_history_error(int err_id);
char					sh_history_print(t_shell *sh);
char					sh_history_print_shift(t_shell *sh, int shift);
char					sh_history_options(t_shell *sh, char **argv);
char					sh_history_options(t_shell *sh, char **argv);
char					sh_history_option_c(t_shell *sh);
char					sh_history_option_d(
							t_shell *sh,
							int *i,
							int *j,
							char **argv);
char					sh_history_option_sp(
							t_shell *sh,
							int *i,
							int *j,
							char **argv);
char					sh_history_option_warn(
							t_shell *sh,
							int *i,
							int *j,
							char **argv);

/*
** functions - setenv
*/
int						sh_setenv_isbin(char *arg);
int						sh_setenv_equal(char *arg);
char					sh_setenv(t_shell *sh, char **argv);
char					sh_setenv_add(t_shell *sh, t_env *env, char *arg);
char					sh_setenv_error(char *key, char *val, int err_id);
char					*sh_setenv_parse(char *arg);

/*
** functions - unsetenv
*/
char					sh_unsetenv(t_shell *sh, char **argv);
char					sh_unsetenv_remove(t_shell *sh, char *arg);
char					sh_unsetenv_error(char *key, int err_id);
char					*sh_unsetenv_parse(char *arg);

/*
** functions - utils
*/
bool					is_option_string(char *s, char *opt);

/*
** structures - binaries
*/
int						bin_get_hash(const char *sh, const int b, const int a);
void					bin_delete_specified_item(t_bin_item *item);
void					bin_delete_item(t_bin *bin, const char *key);
void					bin_delete(t_bin *bin);
void					bin_insert(t_shell *sh, t_bin *b, t_bin_obj *obj);
void					bin_initialize(t_shell *sh, t_env *env, t_bin *bin);
void					bin_gen_list_for_auto_comp(
							t_shell *sh,
							t_bin *bin,
							char *s);
t_bin					*bin_new(t_shell *sh);
t_bin_obj				*bin_search(t_bin *bin, const char *key);
t_bin_obj				*bin_new_obj(t_shell *sh, char *n, char *p, t_stat st);

/*
** structures - commands
*/
void					command_add(t_shell *sh);
void					command_add_str_based(t_shell *sh, char *str);
void					command_delete_all(t_shell *sh);
void					command_delete_by_id(t_shell *sh, unsigned int id);
void					command_import(t_shell *sh);
void					command_export_all(t_shell *sh);
char					*command_execute_fetch(t_env *e, char *p, char **av);

/*
** structures - environment
*/
int						env_get_hash(const char *sh, const int b, const int a);
void					env_delete_specified_item(t_env_item *item);
void					env_delete_item(t_env *env, const char *key);
void					env_delete(t_env *env);
void					env_insert(t_shell *sh, t_env *e, char *k, char *v);
void					env_initialize(t_shell *sh, t_env *env, char **e);
char					*env_search(t_env *env, const char *key);
char					env_delete_item_from_array(t_env *env, const char *key);
t_env					*env_new(t_shell *sh, char **environ);
t_env					*env_copy(t_shell *sh);

/*
** structures - reader
*/
void					read_delete(t_read *read);
t_read					*read_new(t_shell *sh);

/*
** structures - shell
*/
void					sh_delete(t_shell *sh);
void					sh_set_prompt(t_shell *sh);
char					*sh_get_folder_name(t_env *e, char *l, size_t len);
char					*sh_get_git_branch(char *location);
t_shell					*sh_new(char **environ);

/*
** terminal - cursor
*/
void					sh_move_home(t_shell *sh);
void					sh_move_end(t_shell *sh);
void					sh_move_left(t_shell *sh);
void					sh_move_right(t_shell *sh);
void					sh_move_up(t_shell *sh);
void					sh_move_down(t_shell *sh);
void					sh_move_y(t_shell *sh, int y);
void					sh_move_x(t_shell *sh, int x);
void					sh_move_to_xy(t_shell *sh, int x, int y);
void					sh_move_next_word(t_shell *sh);
void					sh_move_previous_word(t_shell *sh);
void					sh_set_rel_pos(t_shell *sh, int delta, int dir);

/*
** terminal - delete
*/
void					sh_delete_char(t_shell *sh);
void					sh_delete_current_char(t_shell *sh);
void					sh_delete_all(t_shell *sh);
void					sh_delete_to_end(t_shell *sh);
void					sh_delete_from_home(t_shell *sh);
void					sh_delete_previous_word(t_shell *sh);
void					sh_delete_next_word(t_shell *sh);

/*
** terminal - history - browse
*/
void					sh_browse_next(t_shell *sh);
void					sh_browse_prev(t_shell *sh);
void					sh_browse_freeze(t_shell *sh);
char					sh_browse_compare(char *command, char *buffer);

/*
** terminal - history - search
*/
void					sh_search_freeze(t_shell *sh);
void					sh_history_search(t_shell *sh);
void					sh_history_bufferize(t_shell *sh, char *line);
void					sh_history_move_cursor(t_shell *sh);
void					sh_history_print_result(t_shell *sh);
void					sh_history_perform_search(t_shell *sh);
void					sh_search_init(t_shell *sh);

/*
** terminal - multilines
*/
void					sh_multilines(t_shell *sh);
void					sh_multilines_close(t_shell *sh);

/*
** terminal - print
*/
void					sh_fill_buffer(t_shell *sh);
void					sh_print_cmd(t_shell *sh, t_cmd *cmd);
void					sh_print_prompt(t_shell *sh);
void					sh_print_str(t_shell *sh, char *str);
void					sh_welcome(void);
void					sh_select_print(t_shell *sh);

/*
** terminal - read
*/
void					sh_read(t_shell *sh);
void					sh_print_prompt(t_shell *sh);
void					sh_read_dispatcher(t_shell *sh);
void					sh_deletion_dispatcher(t_shell *sh);
char					sh_is_arrow_combination(char *s);
char					sh_is_select_combination(char *s);
char					sh_is_delete_combination(char *s);

/*
** terminal - select
*/
void					sh_cut_selection(t_shell *sh);
void					sh_copy_selection(t_shell *sh);
void					sh_paste_selection(t_shell *sh);
void					sh_select_down(t_shell *sh);
void					sh_select_left_char(t_shell *sh);
void					sh_select_left_word(t_shell *sh);
void					sh_select_right_char(t_shell *sh);
void					sh_select_right_word(t_shell *sh);
void					sh_select_end(t_shell *sh);
void					sh_select_home(t_shell *sh);
void					sh_select_up(t_shell *sh);
void					sh_unselect(t_shell *sh);
void					sh_unselect_delete(t_shell *sh, unsigned char c);
void					sh_select_set_pos(t_shell *sh);
int						sh_get_selection_len(t_shell *sh);
int						sh_get_start_rel_from_abs(t_shell *sh);

/*
** terminal - signals
*/
void					signal_catching(void);
void					sh_window_resize(t_shell *sh);

/*
** terminal - auto_cmopletion
*/
bool					auto_completion(t_shell *sh);
void					auto_display(t_shell *sh, t_obj *obj);

#endif
