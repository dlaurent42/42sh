/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 23:43:19 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/07 23:27:16 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
# include "auto_completion.h"
# include "auto_completion_prot.h"

static bool			parse_obj(t_shell *shell, char **argv)
{
	t_obj			*obj;
	t_obj			*last_obj;

	last_obj = NULL;
	argv++;
	if (!(obj = auto_create_obj()))
		return (false);
	if (!(auto_path(obj, ".", *argv)))
	{
		free(obj);
		return (false);
	}
	if (!shell->ac->obj)
		shell->ac->obj = obj;
	else if (last_obj)
		last_obj->next = obj;
	last_obj = obj;
	return (true);
}

static bool			get_binaries(t_shell *shell, char **argv)
{
	t_obj			*obj;
	t_obj			*last_obj;
	t_bin_auto		*bin_auto;

	last_obj = NULL;
	bin_auto = shell->bin->bin_auto;
	if (*argv)
		argv++;
	while (bin_auto)
	{
		if (!(obj = auto_create_obj()))
			return (false);
		if (!(obj->data.str = ft_strdups(bin_auto->name)))
		{
			free(obj);
			return (false);
		}
		if (!shell->ac->obj)
			shell->ac->obj = obj;
		else if (last_obj)
			last_obj->next = obj;
		last_obj = obj;
		bin_auto = bin_auto->next;
	}
	return (true);
}

bool				auto_get_obj(t_shell *shell)
{
	if (shell->ac->auto_mode != AUTO_NON && shell->ac->auto_mode != AUTO_BIN)
	{
		if (!(parse_obj(shell, shell->ac->argv)))
			return (false);
	}
	else if (shell->ac->auto_mode == AUTO_BIN)
	{
		if (!(get_binaries(shell, shell->ac->argv)))
			return (false);
	}
	return (true);
}
