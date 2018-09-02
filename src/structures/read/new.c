/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 18:11:35 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/02 19:57:15 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_read		*read_new(t_shell *shell)
{
	t_read	*read;
	t_winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	if (!(read = (t_read *)ft_memalloc(sizeof(t_read))))
		error_malloc_reader(shell, "t_read");
	read->w_width = w.ws_col;
	bzero(read->buffer, ARG_MAX);
	bzero(read->header, ARG_MAX);
	return (read);
}
