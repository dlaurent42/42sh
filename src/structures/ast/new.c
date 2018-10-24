/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 20:46:06 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/24 13:45:02 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token_tree		*new_tree_node(void)
{
	t_token_tree		*ret;

	if (!(ret = (t_token_tree *)ft_memalloc(sizeof(t_token_tree))))
		return (NULL);
	ret->tokens = NULL;
	ret->size = 0;
	ret->type = 0;
	ret->left = NULL;
	ret->right = NULL;
	return (ret);
}
