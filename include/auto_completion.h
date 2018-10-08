/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 02:41:07 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/08 02:55:26 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTO_COMPLETION_H
# define AUTO_COMPLETION_H

# include "shell.h"

# define RL_BUFSIZE		1024
# define CHRSIZELEN		8

# define AUTO_NON		0
# define AUTO_BIN		1
# define AUTO_REG		2
# define AUTO_WILD		3

# define AT_FIRST		0
# define AT_REST		1

# define MODE_NON		0
# define MODE_CMP		1
# define MODE_STR		2

# define TYPE_IFO		010000
# define TYPE_CHR		020000
# define TYPE_DIR		040000
# define TYPE_BLK		060000
# define TYPE_REG		0100000
# define TYPE_LNK		0120000
# define TYPE_SOCK		0140000
# define TYPE_WHT		0160000

# define COL_IFO		"\x1b[33m"
# define COL_CHR		"\x1b[1;33m"
# define COL_DIR		"\x1b[1;31m"
# define COL_BLK		"\x1b[1;33m"
# define COL_REG		"\x1b[0m"
# define COL_LNK		"\x1b[1;36m"
# define COL_SOCK		"\x1b[32m"
# define COL_WHT		"\x1b[31m"
# define COL_EXE		"\x1b[1;32m"
# define COL_BG			"\x1b[30;47m"
# define COL_CLR		"\x1b[0m"

typedef struct			s_data
{
	int					file_number;

	char				*str;
	char				*parent_path;
	char				*path;

	int					len_of_str;

	unsigned char		no_file	: 1;
	unsigned char		fill	: 7;

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
	t_obj				*current_obj;
	t_obj				*head;
	t_obj				*track;
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

bool					auto_completion(t_shell *shell);
bool					auto_get_obj(t_shell *shell);
void					auto_free_obj(t_obj **obj);
t_obj					*auto_create_obj(void);

void					auto_issuance(t_shell *shell);
void					auto_read_dispatcher(t_shell *shell);
void					auto_clear_selection_screen(t_shell *shell);
void					auto_manage_buffer(t_shell *sh, char *new_display);
bool					auto_get_attributes(t_shell *shell);
void					auto_show_screen(t_shell *shell, t_obj *obj);
void					auto_do_ls(t_shell *shell, t_obj *obj);
void					auto_do_file_admin(t_shell *shell, t_obj *obj);
void					auto_calc_len_file_name(t_shell *shell, t_obj *obj);
void					auto_calculate_number_of_columns(t_shell *shell);
bool					auto_path(t_obj *obj, char *path, char *name);
void					auto_move_up(t_shell *shell);
void					auto_move_down(t_shell *shell);
void					auto_move_left(t_shell *shell);
void					auto_move_right(t_shell *shell);
bool					auto_is_executeable(t_obj *obj);

bool					auto_history(t_shell *shell);

void					auto_sort(t_shell *shell);
bool					auto_sort_alpha(t_shell *shell);

void					auto_display(t_shell *shell, t_obj *obj);
void					auto_file_name(t_shell *shell, t_obj *obj);
void					auto_print_spaces(int diff);
void					auto_free_ac(t_shell *shell);

#endif