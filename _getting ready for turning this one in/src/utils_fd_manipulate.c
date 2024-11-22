/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fd_manipulate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:48:23 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/08 18:48:23 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_input(t_shell *shell, int input_fd)
{
	if (dup2(input_fd, STDIN_FILENO) == -1)
		exit_clean(shell, errno, "set_input(): dup2 failed");
	if (close(input_fd) == -1)
		exit_clean(shell, errno, "set_input(): close failed");
}

void	set_output(t_shell *shell, int output_fd)
{
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		exit_clean(shell, errno, "set_output(): dup2 failed");
	if (close(output_fd) == -1)
		exit_clean(shell, errno, "set_output(): close failed");
}

void	set_infile(t_shell *shell, const char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (errno == EINTR)
		exit_clean(shell, errno, infile);
	if (fd == -1)
	{
		syntax_error(errno, infile);
		errno = 2;
	}
	else
		set_input(shell, fd);
}

void	set_outfile_append(t_shell *shell, const char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (errno == EINTR)
		exit_clean(shell, errno, outfile);
	if (fd == -1)
	{
		syntax_error(errno, outfile);
		errno = 2;
	}
	else
		set_output(shell, fd);
}

void	set_outfile_trunc(t_shell *shell, const char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (errno == EINTR)
		exit_clean(shell, errno, outfile);
	if (fd == -1)
	{
		syntax_error(errno, outfile);
		errno = 2;
	}
	else
		set_output(shell, fd);
}
