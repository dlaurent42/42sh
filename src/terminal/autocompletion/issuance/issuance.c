/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   issuance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 11:55:05 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/08 06:33:22 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
# include "auto_completion.h"

void				auto_issuance(t_shell *shell)
{
	if (shell->ac->auto_mode == AUTO_BIN)
	{
		if (!(shell->ac->file_name = ft_strdup(shell->ac->argv[1])))
			return ;
		shell->ac->file_name_len = ft_strlen(shell->ac->file_name);
		auto_show_screen(shell, shell->ac->obj);
	}
	else
	{
		shell->ac->current_obj = shell->ac->obj;
		if (!auto_get_attributes(shell))
			return ;
		shell->ac->obj = shell->ac->current_obj;
		if (shell->ac->obj->data.dir && !shell->ac->obj->data.no_file)
			auto_do_ls(shell, shell->ac->obj);
	}
}
