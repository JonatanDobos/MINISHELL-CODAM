/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:48:29 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/08 18:48:30 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* signal_print_newline:
*	Prints a newline for noninteractive signal handling.
*/
void	sig_print_newline(int signal)
{
	(void)signal;
	rl_on_new_line();
}

/* signal_reset_prompt:
*	Resets the readline user input prompt for interactive signal handling.
*/
void	sig_reset_prompt(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_child_exit(int signal)// does not work
{
	(void)signal;
	exit(EXIT_FAILURE);
}
