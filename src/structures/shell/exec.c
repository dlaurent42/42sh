/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 17:41:26 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/27 17:51:13 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_exec			*sh_init_exec(t_env *env, t_bin *bin)
{
	t_exec		*ret;

	if (!(ret = (t_exec *)ft_memalloc(sizeof(t_exec))))
		return (NULL);
	ret->env = env;
	ret->bin = bin;
	return (ret);
}

void			sh_destroy_exec(t_exec **exec)
{
	(exec) ? free(*exec) : (0);
	*exec = NULL;
}
