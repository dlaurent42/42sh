/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 19:13:12 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/19 20:15:16 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_delete(t_shell *sh)
{
	if (!sh)
		return ;
	(sh->env) ? env_delete(sh->env) : 0;
	(sh->bin) ? bin_delete(sh->bin) : 0;
	(sh->read) ? read_delete(sh->read) : 0;
	if (sh->termios)
	{
		tcgetattr(0, sh->termios);
		sh->termios->c_lflag = (ICANON | ECHO);
		tcsetattr(0, 0, sh->termios);
		free(sh->termios);
	}
	(sh->prompt.content) ? ft_strdel(&sh->prompt.content) : 0;
	(sh->prompt.location) ? ft_strdel(&sh->prompt.location) : 0;
	free(sh);
}
