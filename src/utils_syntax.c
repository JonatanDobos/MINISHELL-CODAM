/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_syntax.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 08:54:34 by joni          #+#    #+#                 */
/*   Updated: 2024/12/09 08:54:53 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_token_err(const char *token, int len)
{
	write(STDERR_FILENO, TOKEN_ERR, ft_strlen(TOKEN_ERR));
	write(STDERR_FILENO, "\'", 1);
	if (*token)
		write(STDERR_FILENO, token, len);
	else
		write(STDERR_FILENO, "newline", 7);
	write(STDERR_FILENO, "\'\n", 2);
}
