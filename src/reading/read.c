/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 16:10:01 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/01 21:00:32 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_run(t_shell *shell)
{
	(void)shell;
	ft_putendl("\n---Command sent---");
}

static void	sh_read_esc(t_shell *shell, char *buffer)
{
	(void)buffer;
	(void)shell;
	ft_printf(tgoto(tgetstr("ch", NULL), 0, 0));
	ft_printf(tgetstr("im", NULL));
}

static void	sh_read_del(t_shell *shell, char *buffer)
{
	(void)buffer;
	(void)shell;
	ft_printf(tgoto(tgetstr("dc", NULL), 0, 0));
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
