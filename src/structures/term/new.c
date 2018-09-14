/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 02:54:09 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/14 14:53:23 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	term_set_termios(t_shell *shell, t_term *term)
{
	if (!(term->termios = (t_termios *)ft_memalloc(sizeof(t_termios))))
	{
		free(term);
		error_malloc_term(shell, "t_termios");
	}
	if (tcgetattr(0, term->termios) == -1)
	{
		free(term->termios);
		free(term);
		error_no_term_var(shell);
	}
	term->termios->c_lflag &= ~(ICANON);
	term->termios->c_lflag &= ~(ECHO);
	term->termios->c_cc[VMIN] = 1;
	term->termios->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, term->termios) == -1)
	{
		free(term->termios);
		free(term);
		error_no_term_var(shell);
	}
}

static void	term_set_header(t_shell *shell, t_term *term)
{
	if (!(term->header.content = (unsigned char *)getcwd((char *)term->header.content, PATH_MAX)))
	{
		free(term->termios);
		free(term);
		error_malloc_term(shell, "t_header");
	}
	while (term->header.content[term->header.unicode_length])
	{
		if (term->header.content[term->header.unicode_length] >= 0b11000000
		|| term->header.content[term->header.unicode_length] < 0b10000000)
			term->header.display_length++;
		term->header.unicode_length++;
	}
	term->header.display_length++;
	term->header.unicode_length++;
	term->header.display_length_mod = term->header.display_length % term->window.width;
}

t_term		*term_new(t_shell *shell)
{
	char		*name;
	t_term		*term;
	t_winsize	window;

	if (!(name = getenv("TERM")))
		error_no_term_var(shell);
	if (tgetent(NULL, name) == ERR)
		error_no_term_var(shell);
	if (!(term = (t_term *)ft_memalloc(sizeof(t_term))))
		error_malloc_term(shell, "t_term");
	term_set_termios(shell, term);
	ft_putstr(CLEAR_SCREEN);
	ioctl(0, TIOCGWINSZ, &window);
	term->window.width = window.ws_col;
	term->window.height = window.ws_row;
	term_set_header(shell, term);
	return (term);
}
