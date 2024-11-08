/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:47:38 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/08 18:47:39 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_files(t_shell *shell, t_token *token)
{
	const char	**redir = (const char **)token->redirect;
	int			i;

	errno = 0;
	if (redir == NULL)
		return (errno);
	i = 0;
	while (redir[i] && !errno)
	{
		if (!ft_strncmp(redir[i], "<<", 2))
		{
			++i;
			continue ;
		}
		if (!ft_strncmp(redir[i], "<", 1))
			set_infile(shell, redir[i] + skip_redir_ws(redir[i]));
		else if (!ft_strncmp(redir[i], ">>", 2))
			set_outfile_append(shell, redir[i] + skip_redir_ws(redir[i]));
		else if (!ft_strncmp(redir[i], ">", 1))
			set_outfile_trunc(shell, redir[i] + skip_redir_ws(redir[i]));
		++i;
	}
	if (token->heredoc_pipe[0] != -1)
		set_input(shell, token->heredoc_pipe[0]);
	return (errno);
}
