/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 22:12:01 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 12:58:34 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** sh_heredoc expect heredoc to be malloced and valid
**
** examples:
**		cat<<toto	->	heredoc = toto
**		cat << toto	->	heredoc = toto
**		cat <<		-> 	function not called
**		cat <<>		->	function not called
*/

char		sh_heredoc(t_shell *sh, char *heredoc)
{
	if (!heredoc)
		return (1);
	if (!sh->modes.heredoc)
		return (1);
	return (0);
}
