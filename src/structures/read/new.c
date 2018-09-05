/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 18:11:35 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/05 20:04:50 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_read		*read_new(t_shell *shell)
{
	t_read	*read;
	
	if (!(read = (t_read *)ft_memalloc(sizeof(t_read))))
		error_malloc_reader(shell, "t_read");
	return (read);
}
