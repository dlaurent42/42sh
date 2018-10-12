/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:39:05 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/12 22:20:31 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "../libft/include/libft.h"
# include "key_strokes.h"
# include <curses.h>
# include <dirent.h>
# include <limits.h>
# include <pwd.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <term.h>
# include <termios.h>
# include <time.h>
# include <uuid/uuid.h>

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct termios	t_termios;
typedef struct winsize	t_winsize;
typedef struct passwd	t_passwd;

typedef struct			s_cmd_attr
{
	char				*cmd;
	char				**options;
}						t_cmd_attr;

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
	bool				local;
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
	bool				is_new;
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
	char				parsed[ARG_MAX + 1];
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

typedef struct			s_data
{
	int					file_number;

	char				*str;
	char				*parent_path;
	char				*path;

	int					len_of_str;

	int					type;
	mode_t				mode;
	int					links;
	int					rdev;
	char				sym_path[RL_BUFSIZE + 1];

	unsigned char		ifo		: 1;
	unsigned char		chr		: 1;
	unsigned char		dir		: 1;
	unsigned char		blk		: 1;
	unsigned char		reg		: 1;
	unsigned char		lnk		: 1;
	unsigned char		sock	: 1;
	unsigned char		wht		: 1;
	unsigned char		bin		: 1;
	unsigned char		env		: 1;
	unsigned char		no_file	: 1;
	unsigned char		fill	: 5;
}						t_data;

typedef struct			s_obj
{
	t_data				data;
	struct s_obj		*next;
	struct s_obj		*hor_next;
	struct s_obj		*hor_prev;
	struct s_obj		*ver_next;
	struct s_obj		*ver_prev;
}						t_obj;

typedef struct			s_ac
{
	char				**argv;

	char				*pre_file_name;
	char				*del_file_name;
	char				*file_name;
	int					file_name_len;
	char				cmp_mode;
	char				auto_mode;

	unsigned char		at_mode	: 1;
	unsigned char		fill	: 7;

	int					len_file_name;
	int					items_to_display;
	int					total_blocks;
	int					number_of_printed_rows;

	int					width;
	int					height;
	int					number_of_columns;

	t_obj				*obj;
	t_obj				*bin;
	t_obj				*env;
	t_obj				*current_obj;
	t_obj				*select;
	t_obj				*window_resize;
}						t_ac;

typedef struct			s_read_dir
{
	t_obj				*obj;
	t_obj				*tmp;
	t_obj				*head;
	t_obj				*last_obj;
	DIR					*directory;
	struct dirent		*file;
}						t_read_dir;

typedef struct			s_shell
{
	t_ac				*ac;
	char				*hist;
	pid_t				pid;
	t_bin				*bin;
	t_cmd				*cmd;
	t_env				*env;
	t_env				*alias;
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

/*
** functions - builtins
*/
void					sh_add_builtins_to_auto_comp(t_shell *sh, t_bin *bin);

/*
** functions - builtins - alias
*/
int						sh_alias_isbin(char *arg);
int						sh_alias_equal(char *arg);
char					sh_alias_display(t_env *env, bool exportable);
char					sh_alias(t_shell *sh, t_env *env, char **argv);
char					sh_alias_add(t_shell *sh, t_env *env, char *arg);
char					sh_alias_error(char *key, char *val, int id, char *msg);
char					*sh_alias_parse(char *arg);

/*
** functions - builtins - cd
*/
int						sh_cd_remove_troll(char *s);
int						sh_cd_options(char **argv, bool *opt_l, bool *opt_p);
char					sh_cd(t_shell *sh, t_env *env, char **argv);
char					sh_cd_error(char *value, char *path, int err_id);
char					sh_cd_follow(t_shell *sh, t_env *e, char *v, char d);
char					sh_cd_nofollow(t_shell *sh, t_env *e, char *v, char *p);
char					sh_cd_nofollow_dash(
							t_shell *sh,
							t_env *env,
							char *value,
							char *path);
char					*sh_cd_parse_path(char *s);
char					*sh_cd_remove_last_slash(char *param);

/*
** functions - builtins - echo
*/
char					sh_echo(t_shell *sh, t_env *env, char **argv);

/*
** functions - builtins - env
*/
char					sh_env(t_shell *sh, t_env *src, char **argv);
char					sh_env_print(t_env *env);
char					sh_env_error(
							t_env *env,
							t_bin *bin,
							char c,
							int err_id);
char					sh_env_exec(
							t_shell *sh,
							t_env *env,
							t_bin *bin,
							char **arr);

/*
** functions - builtins - exit
*/
char					sh_exit(t_shell *sh, t_env *env, char **argv);

/*
** functions - builtins - export
*/
char					sh_export(t_shell *sh, t_env *env, char **argv);
char					sh_export_add(t_shell *sh, t_env *env, char *arg);
char					sh_export_display(t_env *env, bool exportable);
char					sh_export_error(char *k, char *v, int id, char *msg);
char					*sh_export_parse(char *arg);
int						sh_export_isbin(char *arg);
int						sh_export_equal(char *arg);

/*
** functions - builtins - history
*/
char					sh_history(t_shell *sh, t_env *env, char **argv);
char					sh_history_error(int err_id);
char					sh_history_print(t_shell *sh);
char					sh_history_print_shift(t_shell *sh, int shift);
char					sh_history_options(t_shell *sh, t_env *e, char **argv);
char					sh_history_option_c(t_shell *sh, t_env *env);
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
							t_env *env,
							char *path,
							char c);

/*
** functions - builtins - setenv
*/
int						sh_setenv_isbin(char *arg);
int						sh_setenv_equal(char *arg);
char					sh_setenv(t_shell *sh, t_env *env, char **argv);
char					sh_setenv_add(t_shell *sh, t_env *env, char *arg);
char					sh_setenv_error(char *key, char *val, int err_id);
char					*sh_setenv_parse(char *arg);

/*
** functions - builtins - unalias
*/
char					sh_unalias(t_shell *sh, t_env *env, char **argv);
char					sh_unalias_remove(t_env *env, char *arg);
char					sh_unalias_error(char *key, int err_id);
char					*sh_unalias_parse(char *arg);

/*
** functions - builtins - unset
*/
char					sh_unset(t_shell *sh, t_env *env, char **argv);
char					sh_unset_remove(t_env *env, char *arg);
char					sh_unset_error(char *key, int err_id);
char					*sh_unset_parse(char *arg);

/*
** functions - builtins - unsetenv
*/
char					sh_unsetenv(t_shell *sh, t_env *env, char **argv);
char					sh_unsetenv_remove(t_env *env, char *arg);
char					sh_unsetenv_error(char *key, int err_id);
char					*sh_unsetenv_parse(char *arg);

/*
** functions - builtins - utils
*/
bool					is_option_string(char *s, char *opt);
char					*sh_get_path_from_filename(char *filename);

/*
** functions - exec
*/
char					sh_command_dispatch(
							t_shell *sh,
							t_env *env,
							char **argv);

/*
** functions - exec
*/
char					sh_command_dispatch(t_shell *sh, t_env *env, char **a);
char					sh_command_exec(t_shell *sh, char **cmd, char **env);

/*
** functions - lexer
*/
bool					sh_command_lexer(t_shell *sh, t_env *env, char *str);

/*
** functions - lexer - handlers
*/
bool					sh_command_parse_backslash(char *str);
bool					sh_command_empty(char *str);
bool					sh_command_quotes_check(char *str);
void					sh_command_trim(char *str);
void					sh_remove_useless_quotes(char *str);
void					sh_command_expand_tile(t_shell *sh, t_env *e, char *s);
void					sh_command_expand_dollars(
							t_shell *sh,
							t_env *env,
							char *str);

/*
** functions - lexer - utils
*/
void					sh_command_inject(char *str, char *injection, int i);
void					sh_command_repatriate(char *str, int i, int len);

/*
** functions - parser
*/
char					**sh_command_build(char *str);
bool					sh_is_not_builtin(char *str);
void					sh_command_parser(
							t_shell *sh,
							t_env *env,
							t_bin *bin,
							char *str);

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
t_bin					*bin_update(t_shell *sh, t_env *env, t_bin *bin);
t_bin					*bin_new(t_shell *sh, t_env *env);
t_bin_obj				*bin_search(t_bin *bin, const char *key);
t_bin_obj				*bin_new_obj(t_shell *sh, char *n, char *p, t_stat st);

/*
** structures - commands
*/
void					command_add(t_shell *sh, bool is_new);
void					command_add_str_based(t_shell *sh, char *s, bool isnew);
void					command_append_from(t_shell *sh, t_env *env, char *p);
void					command_append_to(t_shell *sh, t_env *env, char *p);
void					command_delete_all(t_shell *sh);
void					command_delete_by_id(t_shell *sh, unsigned int id);
void					command_import(t_shell *sh);
void					command_import_from(t_shell *sh, t_env *env, char *p);
void					command_export_all(t_shell *sh);
void					command_export_to(t_shell *sh, t_env *env, char *file);

/*
** structures - environment
*/
int						env_get_hash(const char *sh, const int b, const int a);
void					env_delete_specified_item(t_env_item *item);
void					env_delete_item(t_env *env, const char *key);
void					env_delete(t_env *env);
void					env_insert(t_shell *sh, t_env *env, char *k, char *v);
void					env_insert_local(
							t_shell *sh,
							t_env *e,
							char *k,
							char *v);
void					env_initialize(t_shell *sh, t_env *env, char **e);
void					env_initialize_local(t_shell *sh);
void					env_local_to_public(t_env *env, char *key);
void					env_insert_item_into_array(t_env *e, char *k, char *v);
char					*env_search(t_env *env, const char *key);
char					*env_search_public(t_env *env, const char *key);
char					*env_search_local(t_env *env, const char *key);
char					env_delete_item_from_array(t_env *env, const char *key);
t_env					*env_new(t_shell *sh, char **environ);
t_env					*env_copy(t_shell *sh, t_env *src);
t_env_item				*env_new_item(t_shell *sh, t_env *e, char *k, char *v);

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
** terminal - auto_completion
*/
bool					auto_completion(t_shell *sh);
void					auto_display(t_shell *sh, t_obj *obj);
bool					auto_get_obj(t_shell *sh);
void					auto_free_obj(t_obj **obj);
t_obj					*auto_create_obj(void);

void					auto_issuance(t_shell *sh);
void					auto_read_dispatcher(t_shell *sh);
void					auto_clear_selection_screen(t_shell *sh);
bool					auto_get_attributes(t_shell *sh);
void					auto_show_screen(t_shell *sh, t_obj *obj);
void					auto_merge_objs(t_shell *sh, t_obj *obj);
void					auto_do_ls(t_shell *sh, t_obj *obj);
void					auto_do_file_admin(t_shell *sh, t_obj *obj);
void					auto_do_special_modes(t_shell *sh, t_obj *obj);
void					auto_calc_len_file_name(t_shell *sh, t_obj *obj);
void					auto_calculate_number_of_columns(t_shell *sh);
bool					auto_path(t_obj *obj, char *path, char *name);
void					auto_move_up(t_shell *sh);
void					auto_move_down(t_shell *sh);
void					auto_move_left(t_shell *sh);
void					auto_move_right(t_shell *sh);
bool					auto_is_executeable(t_obj *obj);
bool					contains_printable_characters(char *str);
char					*move_past_leading_spaces(char *content);
bool					auto_history(t_shell *sh);
void					auto_hist_double(t_shell *sh, bool *status);
void					auto_hist_number(t_shell *sh, bool *status);
void					auto_hist_name(t_shell *sh, bool *status);

void					auto_sort(t_obj *obj);

void					auto_file_name(t_shell *sh, t_obj *obj);
void					auto_print_spaces(int diff);
void					auto_free_ac(t_shell *sh);

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

#endif
