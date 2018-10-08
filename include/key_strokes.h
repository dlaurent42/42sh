/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_strokes.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 07:09:03 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/08 07:22:10 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_STROKES_H
# define KEY_STROKES_H

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
** escape sequences - clear
*/
# define CLEAR_TO_EOL	"\x1b[K"
# define CLEAR_LINE		"\x1b[M"
# define CLEAR_SCREEN	"\x1b\x5b\x48\x1b\x5b\x32\x4a"

/*
** escape sequences - cursor
*/
# define CURSOR_HIDE	"\x1b\x5b\x3f\x32\x35\x6c"
# define CURSOR_SHOW	"\x1b\x5b\x3f\x31\x32\x6c\x1b\x5b\x3f\x32\x35\x68"

# define SEARCH_PROMPT	"\n\xf0\x9f\x94\x8d  "

#endif
