/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 22:36:12 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/26 02:08:53 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		free_individual_arg(t_obj *obj)
{
	(obj->data.escaped_str != obj->data.str) ? free(obj->data.escaped_str) : 0;
	free(obj->data.str);
	free(obj->data.path);
	free(obj->data.parent_path);
}

void			auto_free_obj(t_obj **head)
{
	t_obj		*obj;
	t_obj		*tmp;

	obj = *head;
	while (obj)
	{
		tmp = obj;
		free_individual_arg(obj);
		obj = obj->next;
		free(tmp);
	}
	*head = NULL;
}
