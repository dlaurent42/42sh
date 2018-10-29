/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 13:55:37 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/29 10:31:53 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		clean_node(t_token_tree *node)
{
	size_t		i;

	i = 0;
	if (!node)
		return ;
	clean_node(node->left);
	clean_node(node->right);
	while (node->tokens[i])
	{
		ft_strdel(&(node->tokens[i]));
		i++;
	}
	ft_memdel((void **)&(node->tokens));
	ft_memdel((void **)&(node->t_type));
	ft_memdel((void **)&(node->blanks));
	ft_memdel((void **)&node);
}

void			clean_tree(t_token_tree *tree)
{
	clean_node(tree);
}
