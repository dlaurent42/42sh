/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 18:11:35 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/19 20:14:37 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_read		*read_new(t_shell *sh)
{
	t_read	*read;

	if (!(read = (t_read *)ft_memalloc(sizeof(t_read))))
		error_malloc_reader(sh, "t_read");
	return (read);
}
