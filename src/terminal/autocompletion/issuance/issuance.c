/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   issuance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 11:55:05 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/07 23:58:26 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				auto_issuance(t_ac *ac)
{
	if (ac->auto_mode == AUTO_BIN)
	{
		if (!(ac->file_name = ft_strdup(ac->argv[1])))
			return ;
		ac->file_name_len = ft_strlen(ac->file_name);
		auto_show_screen(ac, ac->obj);
	}
	else
	{
		ac->current_obj = ac->obj;
		if (!auto_get_attributes(ac))
			return ;
		ac->obj = ac->current_obj;
		if (ac->obj->data.dir && !ac->obj->data.no_file)
			auto_do_ls(ac, ac->obj);
	}
}
