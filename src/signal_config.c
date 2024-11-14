/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:47:59 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/14 23:27:14 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_interactive(void)
{
	struct sigaction	sa;

	ignore_signal(SIGQUIT);
	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = &sighandler_reset_prompt;
	sigaction(SIGINT, &sa, NULL);
}

void	sig_parent(void)
{
	struct sigaction	sa;
	struct sigaction	sb;

	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = &sighandler_semiint_mini;
	sigaction(SIGINT, &sa, NULL);
	ft_memset(&sa, 0, sizeof(sb));
	sigemptyset(&sb.sa_mask);
	sb.sa_flags = 0;
	sb.sa_handler = &sighandler_quit_coredumped;
	sigaction(SIGQUIT, &sb, NULL);
}

void	sig_child(void)
{
	default_signal(SIGINT);
	default_signal(SIGQUIT);
}

void	sig_heredoc_child(void)
{
	struct sigaction	sa;

	ignore_signal(SIGQUIT);
	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = &sighandler_close_fds;
	sigaction(SIGINT, &sa, NULL);
	// default_signal(SIGINT);
}

void	sig_heredoc_parent(void)
{
	ignore_signal(SIGQUIT);
}
