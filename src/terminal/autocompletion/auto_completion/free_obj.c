/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 22:36:12 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/01 08:37:47 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
# include "auto_completion.h"
# include "auto_completion_prot.h"

static void		free_individual_arg(t_obj *obj)
{
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
