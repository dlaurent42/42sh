/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:43:02 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/31 18:57:42 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		error_malloc_sh(t_shell *sh)
{
	(sh) ? sh_delete(sh) : 0;
	ft_putendl_fd("Cannot malloc t_shell structure", 2);
	exit(EXIT_FAILURE);
}

void		error_malloc_env(t_shell *sh, t_env *env, char *name)
{
	char	id;

	id = 0;
	if (sh && sh->env == env)
		id = 1;
	else if (sh && sh->alias == env)
		id = 2;
	(env) ? env_delete(env) : 0;
	(sh && id == 1) ? sh->env = NULL : 0;
	(sh && id == 2) ? sh->alias = NULL : 0;
	(sh) ? sh_delete(sh) : 0;
	ft_putstr_fd("Cannot malloc ", 2);
	ft_putendl_fd(name, 2);
	exit(EXIT_FAILURE);
}

void		error_malloc_bin(t_shell *sh, t_bin *bin, char *name)
{
	(bin) ? bin_delete(bin) : 0;
	(sh) ? sh->bin = NULL : 0;
	(sh) ? sh_delete(sh) : 0;
	ft_putstr_fd("Cannot malloc ", 2);
	ft_putendl_fd(name, 2);
	exit(EXIT_FAILURE);
}

void		error_malloc_reader(t_shell *sh, char *name)
{
	(sh) ? sh_delete(sh) : 0;
	ft_putstr_fd("Cannot malloc ", 2);
	ft_putendl_fd(name, 2);
	exit(EXIT_FAILURE);
}

void		error_malloc_term(t_shell *sh, char *name)
{
	(sh) ? sh_delete(sh) : 0;
	ft_putstr_fd("Cannot malloc ", 2);
	ft_putendl_fd(name, 2);
	exit(EXIT_FAILURE);
}
