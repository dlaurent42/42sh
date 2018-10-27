/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 23:27:06 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/26 23:45:45 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	swap_nodes(t_token_tree **one, t_token_tree **two)
{
	int		type;
	size_t	size;
	char	**tokens;

	type = (*one)->type;
	(*one)->type = (*two)->type;
	(*two)->type = type;
	tokens = (*one)->tokens;
	(*one)->tokens = (*two)->tokens;
	(*two)->tokens = tokens;
	size = (*one)->size;
	(*one)->size = (*two)->size;
	(*two)->size = size;
}

void		tkns_sort(t_token_tree **begin_list)
{
	t_token_tree	*tmp;
	int		sorted;

	if (!(*begin_list))
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		tmp = *begin_list;
		while (tmp->right)
		{
			if (tmp->type > tmp->right->type)
			{
				sorted = 0;
				swap_nodes(&tmp, &tmp->right);
			}
			tmp = tmp->right;
		}
	}
}

void	skip_and_sort(t_token_tree **tkns, t_token_tree **lst_sep)
{
	*tkns = (*tkns)->right;
	(!(*tkns) || in_range((*tkns)->type, 4, 6)) ? tkns_sort(lst_sep) : (0);
}

// int		prev_node_not_fd_aggr(t_token_tree *start, t_token_tree *end)
// {
// 	while (start->right != end)
// 		start = start->right;
// 	return (start->type != 3);
// }
//
// void	tokens_bring_front(t_token_tree **dst, t_token_tree **src)
// {
// 	char	*tmp;
// 	char	**tmp_dst;
// 	char	**tmp_src;
// 	char	**src_data_tab;
//
// 	tmp_dst = (*dst)->tokens;
// 	tmp_src = (*src)->tokens;
// 	src_data_tab = ft_strsplit((*src)->data, ' ');
// 	if (prev_node_not_fd_aggr(*dst, *src))
// 	{
// 		tmp = ft_join_arr_to_str(&(src_data_tab[1]));
// 		(*src)->data = ft_strdup(src_data_tab[0]);
// 		ft_strdel(&tmp_src);
// 	}
// 	else
// 	{
// 		tmp = ft_join_arr_to_str(&(src_data_tab[0]));
// 		tkn_del(*dst, src);
// 	}
// 	(*dst)->data = ft_str3join(tmp_dst, " ", tmp);
// 	ft_strdel(&tmp_dst);
// 	ft_strdel(&tmp);
// 	ft_str2del(&src_data_tab);
// }
