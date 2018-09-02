/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:39:05 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/02 19:57:08 by dlaurent         ###   ########.fr       */
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

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct termios	t_term;
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
	char				cmd[ARG_MAX];
	size_t				cmd_length;
	struct s_cmd		*last;
	struct s_cmd		*prev;
}						t_cmd;

typedef struct			s_read
{
	// Cursor
	unsigned int		cursor_rel_pos; // position in line
	unsigned int		cursor_abs_pos; // position in buffer

	// Modes
	unsigned char		auto_completion_mode; // boolean
	unsigned char		esc_mode;

	// Buffer
	unsigned char		buffer[ARG_MAX];
	unsigned int		buffer_len; // to avoid ft_strlen multiple calls
	t_cmd				*cmd;

	// Header
	unsigned char		header[ARG_MAX];
	unsigned int		header_len; // to avoid ft_strlen multiple calls

	// Window
	unsigned short		w_width; // current window width
}						t_read;

typedef struct			s_shell
{
	t_bin				*bin;
	t_cmd				*cmd;
	t_env				*env;
	t_read				*read;
	t_term				*term;
}						t_shell;

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
** reading
*/
void					sh_read(t_shell *shell);
void					signal_catching(void);

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

#endif
