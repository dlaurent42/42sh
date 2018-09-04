/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 18:11:35 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/04 19:32:45 by dlaurent         ###   ########.fr       */
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
	if (!(read->header = getcwd(read->header, PATH_MAX)))
	{
		free(read);
		error_malloc_reader(shell, "char *");
	}
	read->header_len = ft_strlens(read->header);
	return (read);
}
