/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_new_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:57:26 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/21 17:05:24 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				auto_hist_new_prompt(t_shell *sh, bool *status)
{
	char			*tmp_content;

	if (*status)
		return ;
	*status = true;
	if (ft_strcmp(sh->read->line, K_RETURN))
		return ;
	if ((tmp_content = ft_strdups(sh->buffer.content + sh->buffer.ushift)))
	{
		sh_sigint_reset(sh, "0");
		sh_print_str(sh, tmp_content);
		free(tmp_content);
	}
}
