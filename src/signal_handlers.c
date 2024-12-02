/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handlers.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 18:48:29 by svan-hoo      #+#    #+#                 */
/*   Updated: 2024/12/02 13:17:06 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sighandler_reset_prompt(int sig)
{
	g_signal = sig + 128;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sighandler_quit_coredumped(int sig)
{
	g_signal = sig + 128;
	write(STDERR_FILENO, "Quit\t(core dumped)\n", 20);
	signal(sig, SIG_IGN);
	kill(0, sig);
}

void	sighandler_semiint_mini(int sig)
{
	struct termios	term;

	g_signal = sig + 128;
	if (tcgetattr(STDIN_FILENO, &term) != 0)
		ft_putstr_fd("tcgetattr() failed\n", STDERR_FILENO);
	term.c_lflag |= ICANON;
	term.c_lflag |= ECHO;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
		ft_putstr_fd("tcsetattr() failed\n", STDERR_FILENO);
	write(1, "\n", 1);
}

// void	sighandler_close_fds(int sig)
// {
// 	g_signal = sig + 128;
// }
