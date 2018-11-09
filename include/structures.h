/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 18:01:18 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/09 15:35:10 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "shell.h"

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct termios	t_termios;
typedef struct winsize	t_winsize;
typedef struct passwd	t_passwd;
typedef struct timeval	t_timeval;

int g_exit_code;

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
	char				*full_env[ENV_MAX_SIZE + 1];
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
	char				*parsed;
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
	unsigned char		select			: 1;
	unsigned char		browse			: 1;
	unsigned char		search			: 1;
	unsigned char		multiline		: 1;
	unsigned char		exec			: 1;
	unsigned char		heredoc			: 1;
	unsigned char		globbing		: 1;
	unsigned char		subshell		: 2;
	unsigned char		fill			: 6;
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

typedef struct			s_cbraces
{
	int					start;
	int					stop;
	char				*str;
	char				*before;
	char				*after;
	char				*left;
	char				*right;
	char				**split;
}						t_cbraces;

typedef struct			s_path
{
	char				*path;
	struct s_path		*next;
}						t_path;

typedef struct			s_filesystem
{
	t_path				*paths;
	char				curr_idx;
	char				lst_idx[GLOB_ASCII_MAX + 1];
	char				*lst[GLOB_ASCII_MAX + 1];
}						t_filesystem;

typedef struct			s_glob
{
	bool				starts_by_path;
	bool				ends_by_path;
	char				*result;
	char				**strsplit;
	t_filesystem		**fs;
}						t_glob;

typedef struct			s_lexer_glob
{
	size_t				len;
	char				*s;
	struct s_lexer_glob	*head;
	struct s_lexer_glob	*next;
}						t_lexer_glob;

typedef struct			s_data
{
	int					file_number;

	char				*str;
	char				*escaped_str;
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
	char				*initial_file_name;

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

typedef struct			s_exec
{
	t_env				*env;
	t_bin				*bin;
}						t_exec;

typedef struct			s_heredocs
{
	char				*keyword;
	char				*value;
	bool				closed;
	struct s_heredocs	*next;
}						t_heredocs;

/*
** Lexer
*/
typedef enum			e_token_type
{
	TOKEN_NULL = 0,
	TOKEN_ANDIF = 1,
	TOKEN_ORIF = 2,
	TOKEN_REDIR = 3,
	TOKEN_PIPE = 4,
	TOKEN_AGGREG = 5,
	TOKEN_HEREDOC = 6,
	TOKEN_SEMICOLON = 7,
	TOKEN_AMPERSAND = 7,
	TOKEN_BLANK = 8,
	TOKEN_SINGLEQUOTE = 9,
	TOKEN_DOUBLEQUOTE = 10,
	TOKEN_BACKQUOTE = 11,
	TOKEN_MERGE = 12,
	TOKEN_WORD = 13,
	TOKEN_SUBSHELL = 14,
}						t_token_type;

typedef struct			s_token
{
	char				*id;
	int					size;
	int					blank_before;
	t_token_type		type;
}						t_token;

typedef struct			s_lexer
{
	t_token				*tokens;
	size_t				capacity;
	size_t				size;
	char				*cmd;
	int					word;
}						t_lexer;

/*
** Tokens for AST
*/
typedef struct			s_token_tree
{
	char				**tokens;
	int					*t_type;
	int					*blanks;
	size_t				size;
	int					type;
	struct s_token_tree	*left;
	struct s_token_tree	*right;
}						t_token_tree;

typedef struct			s_process
{
	int					status;
	char				completed;
	char				stopped;
	char				**argv;
	t_env				*env;
	pid_t				pid;
	struct s_process	*next;
}						t_process;

typedef struct			s_job
{
	int					id;
	int					rank;
	char				*command;
	t_process			*first_process;
	pid_t				pgid;
	char				notified;
	char				notifications;
	struct termios		tmodes;
	int					fd[3];
	struct s_job		*next;
}						t_job;

typedef struct			s_shell
{
	t_ac				*ac;
	int					exe;
	char				*hist;
	pid_t				pid;
	t_gnl				*gnl;
	pid_t				shell_pgid;
	char				jc;
	char				jc_muted;
	t_bin				*bin;
	t_cmd				*cmd;
	t_env				*env;
	t_env				*alias;
	t_job				*job;
	t_read				*read;
	t_exec				*exec;
	t_modes				modes;
	t_lexer				lexer;
	t_cursor			cursor;
	t_prompt			prompt;
	t_window			window;
	t_buffer			buffer;
	t_search			search;
	t_select			selection;
	t_termios			termios;
	t_process			*process;
	t_heredocs			*heredocs;
}						t_shell;

t_shell					*g_sh;

#endif
