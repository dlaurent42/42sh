/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 02:54:09 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/15 22:25:17 by dlaurent         ###   ########.fr       */
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

static void	term_init_prompt(t_shell *shell, t_term *term)
{
	unsigned char	*prompt;

	prompt = NULL;
	prompt = (unsigned char *)getcwd((char *)prompt, PATH_MAX);
	term_set_prompt(shell, term, (char *)prompt);
	if (prompt)
		ft_strdel((char **)&prompt);
	if (!term->prompt.content)
	{
		free(term->termios);
		free(term);
		error_malloc_term(shell, "t_prompt");
	}
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
	term_init_prompt(shell, term);
	return (term);
}
