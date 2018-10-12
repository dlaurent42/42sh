/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:12:05 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/12 17:13:54 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_bin	*bin_update(t_shell *sh, t_env *env, t_bin *bin)
{
	bin_delete(bin);
	return (bin_new(sh, env));
}
