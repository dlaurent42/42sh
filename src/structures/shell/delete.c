/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 19:13:12 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/09 21:31:55 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_delete(t_shell *sh)
{
	bool	subshell;

	if (!sh)
		return ;
	process_destroy_all(sh);
	subshell = sh->modes.subshell;
	(sh->ac) ? auto_free_ac(sh) : 0;
	(sh->cmd) ? command_export_all(sh) : 0;
	(sh->cmd) ? command_delete_all(sh) : 0;
	(sh->gnl) ? gnl_delete(sh) : 0;
	(sh->env) ? env_delete(sh->env) : 0;
	(sh->job) ? job_destroy_all(sh->job) : 0;
	(sh->alias) ? env_delete(sh->alias) : 0;
	(sh->bin) ? bin_delete(sh->bin) : 0;
	(sh->read) ? read_delete(sh->read) : 0;
	(sh->exec) ? sh_destroy_exec(&(sh->exec)) : 0;
	(sh->buffer.parsed) ? ft_strdel(&sh->buffer.parsed) : 0;
	(sh->selection.content) ? ft_strdel(&sh->selection.content) : 0;
	(sh->prompt.content) ? ft_strdel(&sh->prompt.content) : 0;
	(sh->prompt.location) ? ft_strdel(&sh->prompt.location) : 0;
	sh_heredoc_delete(sh);
	(subshell == FALSE) ? sh_unset_termios(sh) : 0;
	free(sh);
}
