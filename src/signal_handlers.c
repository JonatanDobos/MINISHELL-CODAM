/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:48:29 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/14 19:45:23 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sighandler_reset_prompt(int sig)
{
	g_signal = sig + 128;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	sighandler_semiint_mini(int sig)
{
	write(1, "\n", 1);
	g_signal = sig + 128;
}

void	sighandler_quit_coredumped(int sig)
{
	g_signal = sig + 128;
	write(STDERR_FILENO, "Quit\t(core dumped)\n", 20);
	signal(sig, SIG_IGN);
	raise(sig);
}
