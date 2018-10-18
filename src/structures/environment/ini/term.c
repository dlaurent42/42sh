/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 11:07:52 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/18 12:23:44 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_env_init_term(t_shell *sh)
{
	if (!(env_search(sh->env, "TERM")) && sh->env->count + 1 < sh->env->size)
		env_insert(sh, sh->env, "TERM", TERM_DEFAULT);
}
