/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 15:04:22 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/09 13:43:33 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** -c   Clear the history list. This can be combined with the other
**      options to replace the history list completely.
** -d offset
**      Delete the history entry at position offset.
**      offset should be specified as it appears when the history is displayed.
** -w   Write out the current history to the history file.
** -a   Append the new history lines (history lines entered since
**      the beginning of the current Bash session) to the history file.
** -r   Read the current history file and append its contents to the history
**      list.
** -n   Append the history lines not already read from the history file
**      to the current history list. These are lines appended to the
**      history file since the beginning of the current Bash session.
** -p   Perform history substitution on the args and display the result
**      on the standard output, without storing the results in the history list.
** -s   The args are added to the end of the history list as a single entry.
*/

char		sh_history_options(t_shell *sh, char **argv)
{
	int		i;
	int		j;
	char	c;
	char	res;

	i = 0;
	res = 0;
	while (argv[i] && res == 0 && argv[i][0] == '-'
	&& !(argv[i][1] == '-' && !argv[i][2]))
	{
		while (res == 0 && argv[i][++j] && (c = argv[i][j]))
			if (c == 'c')
				return (sh_history_option_c(sh));
			else if (c == 'd')
				res = sh_history_option_d(sh, &i, &j, argv);
			else if (c == 'w' || c == 'a' || c == 'r' || c == 'n')
				res = sh_history_option_warn(sh, &i, &j, argv);
			else if (c == 's' || c == 'p')
				return (sh_history_option_sp(sh, &i, &j, argv));
			else
				res = sh_history_error(3);
		i += (argv[i] && res == 0) ? 1 : 0;
	}
	return (res);
}
