/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:43:02 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/25 10:45:14 by azaliaus         ###   ########.fr       */
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
	(env) ? env_delete(env) : 0;
	(sh) ? sh_delete(sh) : 0;
	ft_putstr_fd("Cannot malloc ", 2);
	ft_putendl_fd(name, 2);
	exit(EXIT_FAILURE);
}

void		error_malloc_bin(t_shell *sh, t_bin *bin, char *name)
{
	(bin) ? bin_delete(bin) : 0;
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
