/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:39:05 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/13 22:42:16 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# define K_DEL			"\x7f"
# define CLEAR_SCREEN	"\x1b\x5b\x48\x1b\x5b\x32\x4a"

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct termios	t_termios;
typedef struct winsize	t_winsize;

typedef struct			s_env_item
{
	char				*key;
	char				*value;
}						t_env_item;

typedef struct			s_env
{
	size_t				size;
	size_t				count;
	t_env_item			**items;
}						t_env;

typedef struct			s_bin_obj
{
	char				*name;
	char				path[PATH_MAX + 1];
	t_stat				stats;
}						t_bin_obj;

typedef struct			s_bin_item
{
	char				*key;
	t_bin_obj			*value;
}						t_bin_item;

typedef struct			s_bin
{
	size_t				size;
	size_t				count;
	t_bin_item			**items;
}						t_bin;

typedef struct			s_cmd
{
	char				cmd[ARG_MAX + 1];
	size_t				cmd_length;
	struct s_cmd		*last;
	struct s_cmd		*prev;
	struct s_cmd		*next;
}						t_cmd;

typedef struct			s_cursor
{
	unsigned int		x;
	unsigned int		y;
	unsigned int		abs_pos;
	unsigned int		rel_pos;
}						t_cursor;

typedef struct			s_buffer
{
	unsigned int		unicode_length;
	unsigned int		display_length;
	unsigned char		content[ARG_MAX + 1];
	t_cmd				*cmd;
}						t_buffer;

typedef struct			s_header
{
	unsigned int		unicode_length;
	unsigned int		display_length;
	unsigned int		display_length_mod;
	unsigned char		*content;
}						t_header;

typedef struct			s_read
{
	unsigned char		line[5];
	unsigned char		unicode_bytes_left;
	t_buffer			buffer;
}						t_read;

typedef struct			s_term
{
	unsigned char		auto_completion_mode;
	unsigned char		esc_mode;
	unsigned char		display_mode;
	unsigned short		w_width;
	t_cursor			cursor;
	t_header			header;
	t_termios			*termios;
}						t_term;

typedef struct			s_shell
{
	t_bin				*bin;
	t_cmd				*cmd;
	t_env				*env;
	t_read				*read;
	t_term				*term;
	unsigned char		debug;
}						t_shell;

void					sh_debug(t_shell *shell, char *msg);

/*
** errors
*/
void					error_malloc_shell(t_shell *shell);
void					error_malloc_env(t_shell *s, t_env *e, char *name);
void					error_malloc_bin(t_shell *s, t_bin *b, char *name);
void					error_malloc_reader(t_shell *shell, char *name);
void					error_malloc_term(t_shell *shell, char *name);
void					error_no_path_var(t_shell *shell);
void					error_no_term_var(t_shell *shell);

/*
** functions
*/
void					sh_command_run(t_shell *shell);

/*
** structures - binaries
*/
int						bin_get_hash(const char *s, const int b, const int a);
void					bin_delete_specified_item(t_bin_item *item);
void					bin_delete_item(t_bin *bin, const char *key);
void					bin_delete(t_bin *bin);
void					bin_insert(t_shell *s, t_bin *b, t_bin_obj *obj);
void					bin_initialize(t_shell *shell, t_env *env, t_bin *bin);
t_bin					*bin_new(t_shell *shell);
t_bin_obj				*bin_search(t_bin *bin, const char *key);
t_bin_obj				*bin_new_obj(t_shell *sh, char *n, char *p, t_stat st);

/*
** structures - environment
*/
int						env_get_hash(const char *s, const int b, const int a);
void					env_delete_specified_item(t_env_item *item);
void					env_delete_item(t_env *env, const char *key);
void					env_delete(t_env *env);
void					env_insert(t_shell *s, t_env *e, char *k, char *v);
void					env_initialize(t_shell *shell, t_env *env, char **e);
char					*env_search(t_env *env, const char *key);
t_env					*env_new(t_shell *shell, char **environ);

/*
** structures - reader
*/
void					read_delete(t_read *read);
t_read					*read_new(t_shell *shell);

/*
** structures - shell
*/
void					shell_delete(t_shell *shell);
t_shell					*shell_new(void);

/*
** structures - term
*/
void					term_delete(t_term *term);
t_term					*term_new(t_shell *shell);

/*
** terminal - autocompletion
*/
void					sh_read_autocompletion(t_shell *shell);

/*
** terminal - cursor
*/
void					sh_move_home(t_shell *shell);
void					sh_move_home_xy(t_shell *shell, unsigned int x, unsigned int y);
void					sh_move_end(t_shell *shell);
void					sh_move_left(t_shell *shell);
void					sh_move_right(t_shell *shell);
void					sh_move_to_xy(
							t_shell *shell,
							unsigned int x,
							unsigned int y);
void					sh_set_rel_pos(
							t_shell *shell,
							unsigned int delta,
							int dir);

/*
** terminal - reader
*/
void					sh_read(t_shell *shell);
void					sh_print_header(t_shell *shell);
void					sh_read_delete(t_shell *shell);
void					sh_fill_buffer(t_shell *shell);

/*
** terminal - signals
*/
void					signal_catching(void);

#endif
