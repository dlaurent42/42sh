/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_len_file_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 13:47:37 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/08 08:43:52 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "auto_completion.h"
#include "auto_completion_prot.h"

void				auto_calc_len_file_name(t_shell *sh, t_obj *obj)
{
	int				len;
	char			*str;
	t_data			*data;

	data = &obj->data;
	str = data->str;
	len = ft_strlenu(str);
	data->len_of_str = len;
	if (data->dir || data->lnk || data->sock || data->wht
				|| data->ifo || auto_is_executeable(obj))
		data->len_of_str++;
	len++;
	if (len > sh->ac->len_file_name)
		sh->ac->len_file_name = len;
}
