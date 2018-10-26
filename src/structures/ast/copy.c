/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 11:09:34 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/26 11:15:12 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token_tree		*copy_tree_node(t_token_tree *obj)
{
	t_token_tree		*ret;

	if (!(ret = new_tree_node()))
		return (NULL);
	ret->tokens = ft_str2dup(obj->tokens);
	ret->size = obj->size;
	ret->type = obj->type;
	ret->left = NULL;
	ret->right = NULL;
	return (ret);
}
