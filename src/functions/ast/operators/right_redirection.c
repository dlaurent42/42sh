/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 12:46:49 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/25 13:04:01 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	execute_on_right(t_shell *sh, t_token_tree *tree, int fd)
{
	char	ret;
	int		stdout;

	stdout = dup(1);
	dup2(fd, 1);
	ret = execute_tree(sh, tree->left);
	dup2(stdout, 1);
	close(stdout);
	return (ret);
}

char			execute_right_redirection(t_shell *sh, t_token_tree *tree)
{
	int				fd;
	int				ops;
	char			*file;
	t_token_tree 	*last;

	last = tree->right;
	ops = O_WRONLY | O_CREAT;
	ops |= (!ft_strcmp(tree->tokens[0], ">") ? O_TRUNC : O_APPEND);
	while (last)
	{
		if (last->type == 1)
		{
			ops = O_WRONLY | O_CREAT;
			ops |= (!ft_strcmp(tree->tokens[0], ">") ? O_TRUNC : O_APPEND);
		}
		file = (last->left ? last->left->tokens[0] : last->tokens[0]);
		if ((fd = open(file, ops, 0644)) == -1)
			return (error_file_permissions(file));
		(last->left && last->right ? close(fd) : 0);
		last = last->right;
	}
	return (execute_on_right(sh, tree, fd));
}
