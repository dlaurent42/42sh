/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 13:38:35 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/26 14:04:32 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_welcome(void)
{
	ft_putendl("Welcome");

	ft_putendl("\nMove");
	ft_putendl("  ← .............. move one char to left");
	ft_putendl("  → .............. move one char to right");
	ft_putendl("  ↖ .............. move to begining of line");
	ft_putendl("  ↘ .............. move to end of line");
	ft_putendl("  ⌥ + ← .......... move one word to left");
	ft_putendl("  ⌥ + → .......... move one word to right");
	ft_putendl("  ⌥ + ↑ .......... move one row up");
	ft_putendl("  ⌥ + ↓ .......... move one row down");

	ft_putendl("\nSelect");
	ft_putendl("  ⇧ + ← .......... select left char");
	ft_putendl("  ⇧ + → .......... select right char");
	ft_putendl("  ⇧ + ↖ .......... select chars to begining of line");
	ft_putendl("  ⇧ + ↘ .......... select chars to end of line");
	ft_putendl("  ⇧ + ⌥ + ← ...... select left word");
	ft_putendl("  ⇧ + ⌥ + → ...... select right word");
	ft_putendl("  ⇧ + ⌥ + ↑ ...... select row above");
	ft_putendl("  ⇧ + ⌥ + ↓ ...... select row below");

	ft_putendl("\nCopy/Cut/Paste");
	ft_putendl("  Ctrl + ⇧ + C ... copy");
	ft_putendl("  Ctrl + ⇧ + X ... cut");
	ft_putendl("  Ctrl + ⇧ + V ... paste");
}
