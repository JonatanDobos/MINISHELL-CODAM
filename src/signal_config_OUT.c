/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_config_OUT.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:47:59 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/22 19:10:06 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// maybe use ioctl().
// maybe use functions with statics to save pid's and hd-fd's in other functions and use in sighandlers.
// void	sighandler_reset_prompt(int sig)
// {
// 	g_signal = sig + 128;
// 	rl_replace_line("", 0);
// 	write(STDOUT_FILENO, "\n", 1);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

void	sig_interactive(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = &sighandler_reset_prompt;
	sigaction(SIGINT, &sa, NULL);
	// signal(SIGINT, &sighandler_reset_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_parent(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

// void	sig_heredoc_child(void)
// {
// 	struct sigaction	sa;

// 	ignore_signal(SIGQUIT);
// 	ft_memset(&sa, 0, sizeof(sa));
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = 0;
// 	sa.sa_handler = &sighandler_close_fds;
// 	sigaction(SIGINT, &sa, NULL);
// 	// default_signal(SIGINT);
// }

// void	sig_heredoc_parent(void)
// {
// 	ignore_signal(SIGQUIT);
// }
