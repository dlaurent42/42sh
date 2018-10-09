/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.warn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:32:31 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/09 22:22:34 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		sh_history_option_warn(t_shell *sh, int *i, int *j, char **argv)
{
	char	c;
	char	*path;

	c = argv[*i][*j];
	path = (argv[*i + 1])
		? sh_get_path_from_filename(argv[*i + 1])
		: NULL;
	if (argv[*i][*j + 1] != '\0')
		return (0);
	(c == 'w') ? command_export_to(sh, path) : 0;
	(c == 'a') ? command_append_to(sh, path) : 0;
	(c == 'r') ? command_import_from(sh, path) : 0;
	(c == 'n') ? command_append_from(sh, path) : 0;
	ft_strdel(&path);
	return (0);
}
