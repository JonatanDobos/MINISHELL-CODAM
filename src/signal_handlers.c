/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:48:29 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/15 00:06:08 by svan-hoo         ###   ########.fr       */
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
	g_signal = sig + 128;
	write(1, "\n", 1);
}

void	sighandler_close_fds(int sig)
{
	g_signal = sig + 128;
	//
	signal(sig, SIG_DFL);
	raise(sig);
}

void	sighandler_quit_coredumped(int sig)
{
	g_signal = sig + 128;
	write(STDERR_FILENO, "Quit\t(core dumped)\n", 20);
	signal(sig, SIG_IGN);
	raise(sig);
}
