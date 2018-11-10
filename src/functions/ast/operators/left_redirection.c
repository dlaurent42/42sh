/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:44:04 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/10 16:00:39 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*get_fd(char *token)
{
	int			i;
	char		*ret;

	ret = NULL;
	i = 0;
	while (token[i] && token[i] != '<')
		i++;
	if (i > 0)
		ret = ft_strndup(token, i);
	return (ret);
}

static char	single_left_cursor(t_shell *sh, t_token_tree *tree, int fd)
{
	int		stdin;
	char	ret;
	char	*front;
	int		fd_targ;

	front = get_fd(tree->tokens[0]);
	fd_targ = (front ? ft_atoi(front) : 0);
	ft_strdel(&front);
	stdin = dup(fd_targ);
	dup2(fd, fd_targ);
	ret = execute_tree(sh, tree->left);
	dup2(stdin, fd_targ);
	(stdin != -1) ? close(stdin) : (0);
	close(fd);
	return (ret);
}

static int	is_token_heredoc(char *token)
{
	int		i;

	i = 0;
	while (token[i] && token[i] != '<')
		i++;
	return ((!ft_strcmp(token + i, "<<")));
}

char		execute_left_redirection(t_shell *sh, t_token_tree *tree)
{
	int					fd;
	int					type;
	int					hdoc_count;
	char				*file;
	t_token_tree		*last;

	last = tree->right;
	type = (is_token_heredoc(tree->tokens[0]) ? 2 : 1);
	hdoc_count = (type == 2 ? 1 : 0);
	while (last)
	{
		file = (last->left) ? last->left->tokens[0] : last->tokens[0];
		if (type == 1 && ((fd = open(file, O_RDONLY)) == -1))
			return (error_execution_file(sh, file));
		(last->left && last->right) ? close(fd) : 0;
		if (last->right)
		{
			type = (is_token_heredoc(tree->tokens[0]) ? 2 : 1);
			hdoc_count += (type == 2 ? 1 : 0);
		}
		last = last->right;
	}
	if (type == 1)
		return (single_left_cursor(sh, tree, fd));
	return (left_heredoc(sh, tree, hdoc_count));
}
