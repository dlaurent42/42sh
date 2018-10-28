/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 13:59:17 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/28 16:38:58 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		sh_heredoc_init(t_shell *sh, char *heredoc)
{
	char	status;

	sh_heredoc_delete(sh);
	status = sh_heredoc_add(sh, heredoc);
	sh->modes.heredoc = (status == STATUS_HEREDOC) ? TRUE : FALSE;
	return (status);
}
