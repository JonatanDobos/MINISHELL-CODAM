#include "../minishell.h"

static bool	check_for_heredoc(char **redir)
{
	int	i;

	i = 0;
	while (redir[i] && ft_strncmp(redir[i], "<<", 2))
		++i;
	return (i != ft_array_size(redir));
}

static void	check_infile(char *infile)
{
	int	tmp_errno;

	if (access(infile, R_OK))
	{
		tmp_errno = errno;
		syntax_error(errno, infile);
		errno = tmp_errno;
	}
}

static void	open_no_heredoc(t_shell *shell, char **redir)
{
	int	i;

	i = 0;
	while (redir[i])
	{
		if (!ft_strncmp(redir[i], "<", 1))
			set_infile(shell, redir[i] + skip_redir_ws(redir[i]));
		else if (!ft_strncmp(redir[i], ">>", 2))
			set_outfile_append(shell, redir[i] + skip_redir_ws(redir[i]));
		else if (!ft_strncmp(redir[i], ">", 1))
			set_outfile_trunc(shell, redir[i] + skip_redir_ws(redir[i]));
		if (errno)
			break ;
		i++;
	}
}

static void	open_with_heredoc(t_shell *shell, char **redir)
{
	int	i;

	i = 0;
	while (redir[i] && ft_strncmp(redir[i], "<<", 2) && !errno)
	{
		if (!ft_strncmp(redir[i], "<", 1))
			check_infile(redir[i] + skip_redir_ws(redir[i]));
		else if (!ft_strncmp(redir[i], ">>", 2))
			set_outfile_append(shell, redir[i] + skip_redir_ws(redir[i]));
		else if (!ft_strncmp(redir[i], ">", 1))
			set_outfile_trunc(shell, redir[i] + skip_redir_ws(redir[i]));
		++i;
	}
	while (redir[i] && errno != ENOMEM)
	{
		here_doc(shell, redir[i] + skip_redir_ws(redir[i]));
		++i;
	}
}

void	open_files(t_shell *shell, t_token *token)
{
	if (token->redirect == NULL)
		return ;
	errno = 0;
	if (check_for_heredoc(token->redirect))
		return (open_with_heredoc(shell, token->redirect));
	else
		return (open_no_heredoc(shell, token->redirect));
}
