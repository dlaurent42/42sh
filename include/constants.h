/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 07:09:03 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/09 12:15:14 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

/*
** key stroke
*/
# define K_UP			"\x1b\x5b\x41"
# define K_DOWN			"\x1b\x5b\x42"
# define K_RIGHT		"\x1b\x5b\x43"
# define K_LEFT			"\x1b\x5b\x44"
# define K_END			"\x1b\x5b\x46"
# define K_HOME			"\x1b\x5b\x48"
# define K_COL_0		"\x1b\x5b\x31\x47"
# define K_COL_ROW_0	"\x1b\x5b\x48"
# define K_TAB			"\x09"
# define K_RETURN		"\x0a"
# define K_DEL			"\x7f"
# define K_DEL_ALL		"\x1b\x5b\x4a"

/*
** ⌥ + key stroke
*/
# define K_O_UP			"\x1b\x1b\x5b\x41"
# define K_O_DOWN		"\x1b\x1b\x5b\x42"
# define K_O_RIGHT		"\x1b\x1b\x5b\x43"
# define K_O_LEFT		"\x1b\x1b\x5b\x44"

/*
** ⇧ + key stroke
*/
# define K_S_UP			"\x1b\x5b\x31\x3b\x32\x41"
# define K_S_DOWN		"\x1b\x5b\x31\x3b\x32\x42"
# define K_S_RIGHT		"\x1b\x5b\x31\x3b\x32\x43"
# define K_S_LEFT		"\x1b\x5b\x31\x3b\x32\x44"
# define K_S_END		"\x1b\x5b\x31\x3b\x32\x46"
# define K_S_HOME		"\x1b\x5b\x31\x3b\x32\x48"

/*
** ⇧ + ⌥ + key stroke
*/
# define K_S_O_UP		"\x1b\x5b\x31\x3b\x31\x30\x41"
# define K_S_O_DOWN		"\x1b\x5b\x31\x3b\x31\x30\x42"
# define K_S_O_RIGHT	"\x1b\x5b\x31\x3b\x31\x30\x43"
# define K_S_O_LEFT		"\x1b\x5b\x31\x3b\x31\x30\x44"
# define K_S_O_END		"\x1b\x5b\x31\x3b\x31\x30\x46"
# define K_S_O_HOME		"\x1b\x5b\x31\x3b\x31\x30\x48"

/*
** fn + key stroke
*/
# define K_F_DEL		"\x1b\x5b\x33\x7e"

/*
** escape sequences - clear
*/
# define CLEAR_HIST		"\x1b[3J"
# define CLEAR_TO_EOL	"\x1b[K"
# define CLEAR_LINE		"\x1b[M"
# define CLEAR_SCREEN	"\x1b\x5b\x48\x1b\x5b\x32\x4a"

/*
** escape sequences - cursor
*/
# define CURSOR_HIDE	"\x1b\x5b\x3f\x32\x35\x6c"
# define CURSOR_SHOW	"\x1b\x5b\x3f\x31\x32\x6c\x1b\x5b\x3f\x32\x35\x68"

/*
** escape sequences - prompt (search)
*/
# define SEARCH_PROMPT	"\n\xf0\x9f\x94\x8d  "

/*
** escape sequences - colors
*/
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
# define COL_SELCT		"\x1b[7;37;40m"
# define COL_FOLDER		"\x1b[1;32;40m"
# define COL_WHIGHLIGHT	"\e[7;37;40m"

/*
** autocompletion
*/
# define RL_BUFSIZE		1024
# define CHRSIZELEN		8

# define AUTO_NON		0
# define AUTO_BIN		1
# define AUTO_REG		2
# define AUTO_WILD		3
# define AUTO_ENV		4

# define AT_FIRST		0
# define AT_REST		1

# define MODE_NON		0
# define MODE_CMP		1
# define MODE_STR		2

# define FILT_CD		1
# define FILT_GCC		2

# define TYPE_IFO		010000
# define TYPE_CHR		020000
# define TYPE_DIR		040000
# define TYPE_BLK		060000
# define TYPE_REG		0100000
# define TYPE_LNK		0120000
# define TYPE_SOCK		0140000
# define TYPE_WHT		0160000

/*
** builtins - read
*/
# define READ_MAX_VAR	25
# define READ_D			0
# define READ_E			1
# define READ_N			2
# define READ_P			3
# define READ_R			4
# define READ_S			5
# define READ_T			6
# define READ_U			7
# define READ_N_OPTIONS	8
# define READ_SIZE		1

/*
** terminal
*/
# ifndef ARG_MAX
#  define ARG_MAX 		262144
# endif
# define LINE_SIZE		9

/*
** history
*/
# define VERIF_KEY		"j3Y72kqqTtENSVPoufEpmMB0sbQsr9Tt"
# define VERIF_KEY_LEN	32
# define SEARCH_LEN		3

/*
** environment
*/
# define ENV_MAX_SIZE	98317
# define ENV_PRIME_1	53
# define ENV_PRIME_2	97
# define TERM_DEFAULT	"xterm-256color"

/*
** prompt
*/
# define GIT_EXT		".git"
# define GIT_HEAD		"/.git/HEAD"
# define GIT_NAME_L		" \x1b[1;34;40mgit[\x1b[1;31;40m"
# define GIT_NAME_R		"\x1b[1;34;40m]"
# define MULT_PROMPT	" \x1b[1;31;40m\xe1\x90\x85\x1b[0m "
# define ERR_PROMPT		" \x1b[1;31;40m▸\x1b[0m "
# define VALID_PROMPT	" \x1b[1;32;40m▸\x1b[0m "

/*
** binaries
*/
# define BIN_MAX_SIZE	98317
# define BIN_PRIME_1	53
# define BIN_PRIME_2	97

/*
** lexer status codes
*/
# define STATUS_EMPTY	            -2
# define STATUS_ERR		            -1
# define STATUS_OK		            0
# define STATUS_DQUOTE	            1
# define STATUS_SQUOTE	            2
# define STATUS_BQUOTE	            3
# define STATUS_HEREDOC	            4
# define STATUS_PIPE	            5
# define STATUS_NEWLINE             6
# define STATUS_SUBSHELL            7
# define STATUS_PERMISSION_DENIED	126
# define STATUS_NOT_FOUND	        127
/*
** # define STATUS_WHEREISBRACKET      66
** # define STATUS_SQUARE              8
** # define STATUS_CURLY               9
*/

/*
** globbing
*/
# define GLOB_MAX_PATHS	125
# define GLOB_ASCII_MAX	30

/*
** backtick
*/
# define BACKTICK_BUFF	256

/*
** job control
*/
# define JOBS_FG	1
# define JOBS_BG	0

#endif
