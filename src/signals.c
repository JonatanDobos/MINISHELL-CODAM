/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:47:59 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/08 18:47:59 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ignore_sigquit:
*	Replaces SIGQUIT signals (ctrl-\) with SIG_IGN to ignore
*	the signal.
*/
void	ignore_sigquit(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

/* set_signals_interactive:
*	Sets the behavior in response to SIGINT (ctrl-c) and SIGQUIT (ctrl-\).
*	SIGINT resets the user input prompt to a new blank line.
*	SIGQUIT is ignored.
*	Used when minishell is in interactive mode, meaning it is awaiting
*	user input.
*/
void	sig_interactive(void)
{
	struct sigaction	sa;

	ignore_sigquit();
	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = &sig_reset_prompt;
	sigaction(SIGINT, &sa, NULL);
}

/* set_signals_noninteractive:
*	Sets the behavior in response to SIGINT (ctrl -c) and SIGQUIT (ctrl -\).
*	Used when minishell is in noninteractive mode, meaning it is not awaiting
*	user input. For example, when a command is running (i.e. cat), minishell
*	should not react to SIGINT and SIGQUIT because only the running process (cat)
*	needs to react to those signals.
*/
void	sig_noninteractive(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = &sig_print_newline;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	sig_child(void)
{
	struct sigaction	sa;

	ignore_sigquit();
	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = &sig_child_exit;
	sigaction(SIGINT, &sa, NULL);
}
