/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:39:05 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/27 11:48:05 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "../libft/include/libft.h"
# include <curses.h>
# include <dirent.h>
# include <signal.h>
# include <term.h>
# include <termios.h>
# include <time.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>

# ifndef ARG_MAX
#  define ARG_MAX 		262144
# endif

# define ENV_MAX_SIZE	999
# define ENV_PRIME_1	3
# define ENV_PRIME_2	13

# define BIN_MAX_SIZE	9999
# define BIN_PRIME_1	3
# define BIN_PRIME_2	13

# define K_UP			"\x1b\x5b\x41"
# define K_DOWN			"\x1b\x5b\x42"
# define K_RIGHT		"\x1b\x5b\x43"
# define K_LEFT			"\x1b\x5b\x44"
# define K_END			"\x1b\x5b\x46"
# define K_HOME			"\x1b\x5b\x48"
# define K_COL_0		"\x1b\x5b\x31\x47"
# define K_COL_ROW_0	"\x1b\x5b\x48"
# define K_DEL			"\x7f"
# define K_DEL_ALL		"\x1b\x5b\x4a"
# define CLEAR_SCREEN	"\x1b\x5b\x48\x1b\x5b\x32\x4a"

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
	char				*environment[ENV_MAX_SIZE];
	size_t				size;
	size_t				count;
	t_env_item			**items;
}						t_env;

typedef struct			s_cmd
{
	char				cmd[ARG_MAX + 1];
	size_t				cmd_len;
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
	int					scroll_y;
}						t_cursor;

typedef struct			s_buffer
{
	int					unicode_len;
	int					display_len;
	char				content[ARG_MAX + 1];
	t_cmd				*cmd;
}						t_buffer;

typedef struct			s_prompt
{
	int					rows;
	int					len;
	int					len_mod;
	char				*content;
	char				*location;
}						t_prompt;

typedef struct			s_read
{
	char				line[7];
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
	unsigned char		others			: 5;
}						t_modes;

typedef struct			s_shell
{
	t_bin				*bin;
	t_cmd				*cmd;
	t_env				*env;
	t_read				*read;
	t_modes				modes;
	t_cursor			cursor;
	t_prompt			prompt;
	t_window			window;
	t_buffer			buffer;
	t_termios			*termios;
}						t_shell;

t_shell					*g_sh;

void					sh_debug(t_shell *sh, char *msg, char *str);
/*
** ------------------- auto_completion structs ---------------------
*/

typedef struct		s_data
{
	int				file_number;

	char			*str;
	char			*parent_path;
	char			*path;

	int				len_of_str;

	unsigned char	no_file	: 1;
	unsigned char	fill	: 7;

	int				type;
	mode_t			mode;
	int				links;
	int				rdev;
	char			sym_path[RL_BUFSIZE + 1];

	unsigned char	ifo		: 1;
	unsigned char	chr		: 1;
	unsigned char	dir		: 1;
	unsigned char	blk		: 1;
	unsigned char	reg		: 1;
	unsigned char	lnk		: 1;
	unsigned char	sock	: 1;
	unsigned char	wht		: 1;
}					t_data;

typedef struct		s_args
{
	t_data			data;
	struct s_args	*next;
	struct s_args	*show_next;
	struct s_args	*show_prev;
}					t_args;

typedef struct		s_frame
{
	char			**argv;

	char			*malloc_failed;

	char			*file_name;
	int				file_name_len;
	char			cmp_mode;

	unsigned char	at_mode	: 1;
	unsigned char	fill	: 7;

	int				len_file_name;
	int				items_to_display;
	int				total_blocks;

	int				width;
	int				number_of_columns;

	t_args			*args;
	t_args			*current_args;
	t_args			*head;
	t_args			*track;
	t_args			*select;

	t_shell			*shell;

	bool			(*sort_function)(struct s_frame *frame);
}					t_frame;

typedef struct		s_read_dir
{
	t_frame			*frame;
	t_args			*args;
	t_args			*tmp;
	t_args			*head;
	t_args			*last_args;
	DIR				*directory;
	struct dirent	*file;
}					t_read_dir;


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
** structures - binaries
*/
int						bin_get_hash(const char *sh, const int b, const int a);
void					bin_delete_specified_item(t_bin_item *item);
void					bin_delete_item(t_bin *bin, const char *key);
void					bin_delete(t_bin *bin);
void					bin_insert(t_shell *sh, t_bin *b, t_bin_obj *obj);
void					bin_initialize(t_shell *sh, t_env *env, t_bin *bin);
char					*bin_execute_fetch(t_shell *sh, char *path, char **av);
t_bin					*bin_new(t_shell *sh);
t_bin_obj				*bin_search(t_bin *bin, const char *key);
t_bin_obj				*bin_new_obj(t_shell *sh, char *n, char *p, t_stat st);

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
t_env					*env_new(t_shell *sh, char **environ);

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
** terminal - autocompletion
*/
void					sh_read_autocompletion(t_shell *sh);

/*
** terminal - cursor
*/
void					sh_move_home(t_shell *sh);
void					sh_move_end(t_shell *sh);
void					sh_move_left(t_shell *sh);
void					sh_move_right(t_shell *sh);
void					sh_move_to_xy(t_shell *sh, int x, int y);
void					sh_move_next_word(t_shell *sh);
void					sh_move_previous_word(t_shell *sh);
void					sh_set_rel_pos(t_shell *sh, int delta, int dir);

/*
** terminal - printer
*/
void					sh_fill_buffer(t_shell *sh);
void					sh_print_prompt(t_shell *sh);
void					sh_print_str(t_shell *sh, char *str);

/*
** terminal - reader
*/
void					sh_read(t_shell *sh);
void					sh_print_prompt(t_shell *sh);
void					sh_read_delete(t_shell *sh);

/*
** terminal - signals
*/
void					signal_catching(void);
void					sh_window_resize(t_shell *sh);

/*
** terminal - auto_completion
*/
void				get_args(t_frame *frame);
void				free_args(t_frame *frame, t_args **args);
t_args				*create_args(void);

void				issuance(t_frame *frame);
void				get_attributes(t_frame *frame);
void				loop_dirs(t_frame *frame);
void				loop_valid_dir(t_frame *frame, t_args *args);
void				do_ls(t_frame *frame, t_args *args);
void				do_file_admin(t_frame *frame, t_args *args);
void				calc_len_file_name(t_frame *frame, t_args *args);
void				calculate_number_of_columns(t_frame *frame);
void				path(t_frame *frame, t_args *args, char *path, char *name);
void				move_right(t_frame *frame);
void				move_left(t_frame *frame);
bool				is_executeable(t_args *args);

void				sort(t_frame *frame);
bool				sort_alpha(t_frame *frame);

void				display(t_frame *frame, t_args *args);
void				file_name(t_frame *frame, t_args *args);
void				print_spaces(int diff);
int					get_diff(t_frame *frame, char *str, long long num, int flag);

void				error_exit(t_frame *frame, char *error_str);
void				free_frame(t_frame *frame);

#endif
