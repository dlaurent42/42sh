/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 13:38:52 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/10 13:41:00 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_redir			*redir_new(void)
{
	t_redir		*ret;

	if (!(ret = (t_redir *)ft_memalloc(sizeof(t_redir))))
		return (NULL);
	return (ret);
}
