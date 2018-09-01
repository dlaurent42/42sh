/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 16:10:01 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/01 22:05:12 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cb: empty current line from beginning to cursor
// nd: move 1 char to left
// le: move 1 char to right

// co: number of columns
// li: numner of lines

static void	cmd_run(t_shell *shell)
{
	(void)shell;
	struct winsize w;

    ioctl(0, TIOCGWINSZ, &w);
	ft_printf("\nNumber of columns: %d\nNumber of lines: %d\n", w.ws_col, w.ws_row);
	ft_putendl("\n---Command sent---");
}

static void	sh_read_esc(t_shell *shell, char *buffer)
{
	(void)buffer;
	(void)shell;
	if (buffer[1] != 91)
		return ;
	if (buffer[2] == 65)// up arrow
		return ;
	else if (buffer[2] == 66)// down arrow
		return ;
	else if (buffer[2] == 67) // right arrow
		ft_putstr(tgoto(tgetstr("nd", NULL), 0, 0));
	else if (buffer[2] == 68)// left arrow
		ft_putstr(tgoto(tgetstr("le", NULL), 0, 0));
}

static void	sh_read_del(t_shell *shell, char *buffer)
{
	(void)buffer;
	(void)shell;
	ft_putstr(tgoto(tgetstr("le", NULL), 0, 0));
	ft_putstr(tgetstr("dc", NULL));
	// ft_printf(tgoto(tgetstr("cb", NULL), 0, 0));
}

void		sh_read(t_shell *shell)
{
	char			buffer[3];
	unsigned char	i;

	bzero(buffer, 4);
	while (TRUE)
	{
		read(0, buffer, 3);
		if (buffer[0] == 4)
			break ;
		else if (buffer[0] == 27)
			sh_read_esc(shell, buffer);
		else if (buffer[0] == 127)
			sh_read_del(shell, buffer);
		else
		{
			i = 0;
			while (buffer[i])
			{
				if (buffer[i] == 10)
					cmd_run(shell);
				else
					ft_printf("%c", buffer[i]);
				i++;
			}
		}
		bzero(buffer, 4);
	}
}
