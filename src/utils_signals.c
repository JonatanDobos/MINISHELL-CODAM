/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:48:29 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/11 20:33:11 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// extern int	g_signal;

// /* signal_print_newline:
// *	Prints a newline for noninteractive signal handling.
// */
// void	sig_print_newline(int signal)
// {
// 	(void)signal;
// 	rl_on_new_line();
// }

/* signal_reset_prompt:
*	Resets the readline user input prompt for interactive signal handling.
*/
void	sig_reset_prompt(int signal)
{
	g_signal = signal;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

// void	sig_newline(int signal)
// {
// 	(void)signal;
// }

void	sig_semiint_mini(int signal)
{
	write(1, "\n", 1);
	g_signal = signal;
}

// void	sig_add_newline(int signal)
// {
// 	(void)signal;
// 	write(1, "\n", 1);
// }
