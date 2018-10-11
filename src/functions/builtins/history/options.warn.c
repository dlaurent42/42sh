/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.warn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:32:31 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 12:26:47 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		sh_history_option_warn(t_shell *sh, t_env *env, char *path, char c)
{
	path = (path) ? sh_get_path_from_filename(path) : NULL;
	(c == 'w') ? command_export_to(sh, env, path) : 0;
	(c == 'a') ? command_append_to(sh, env, path) : 0;
	(c == 'r') ? command_import_from(sh, env, path) : 0;
	(c == 'n') ? command_append_from(sh, env, path) : 0;
	ft_strdel(&path);
	return (0);
}
