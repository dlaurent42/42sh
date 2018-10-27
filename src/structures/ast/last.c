/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 11:18:55 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/26 11:21:10 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token_tree		*get_tree_last_node(t_token_tree *list)
{
	if (!list)
		return (NULL);
	while (list->right)
		list = list->right;
	return (list);
}
