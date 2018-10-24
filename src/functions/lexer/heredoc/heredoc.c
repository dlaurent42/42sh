/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 22:12:01 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 12:38:57 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		sh_heredoc(t_shell *sh, char *heredoc)
{
	if (!sh->modes.heredoc)
		return (!sh_heredoc_has_any(sh));
	return (sh_heredoc_update(sh));
}
