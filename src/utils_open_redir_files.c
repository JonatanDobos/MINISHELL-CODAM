#include "../minishell.h"

static void	check_infile(char *infile)
{
	if (access(infile, R_OK))
	{
		syntax_error(errno, infile);
		errno = 2;
	}
}

static bool	check_for_heredoc(char **redirects)
{
	int	i;

	i = 0;
	while (redirects && redirects[i])
	{
		if (ft_strncmp(redirects[i], "<<", 2))
			return (true);
		++i;
	}
	return (false);
}

void	open_files(t_shell *shell, char **redir)
{
	int			i;
	const bool	has_heredoc = check_for_heredoc(redir);

	if (redir == NULL)
		return ;
	i = 0;
	while (redir[i] && !errno)
	{
		if (!ft_strncmp(redir[i], "<<", 2))
		{
			++i;
			continue ;
		}
		if (!ft_strncmp(redir[i], "<", 1)){
			if (has_heredoc)
				check_infile(redir[i] + skip_redir_ws(redir[i]));
			else
				set_infile(shell, redir[i] + skip_redir_ws(redir[i]));}
		else if (!ft_strncmp(redir[i], ">>", 2))
			set_outfile_append(shell, redir[i] + skip_redir_ws(redir[i]));
		else if (!ft_strncmp(redir[i], ">", 1))
			set_outfile_trunc(shell, redir[i] + skip_redir_ws(redir[i]));
		++i;
	}
}

void	open_heredocs(t_shell *shell, char **redir, int *standup, int *pipe)
{
	bool		has_heredoc;
	int			i;

	if (redir == NULL)
		return ;
	i = 0;
	while (redir[i] && errno != ENOMEM)
	{
		if (!ft_strncmp(redir[i], "<<", 2))
			builtin_heredoc(shell, redir[i] + skip_redir_ws(redir[i]), standup, pipe);
		++i;
	}
}

int	inp_outp_manager(t_shell *shell, t_token *token, int *standup, int *pipe)
{
	errno = 0;
	if (close(pipe[0]) ==  -1)
		return (errno);
	if (token->redirect)
		open_heredocs(shell, token->redirect, standup, pipe);
	if (errno)
		return (errno);
	if (close(standup[0]) == -1)
		return (errno);
	determine_output(shell, token->next, standup, pipe);
	if (token->redirect)
		open_files(shell, token->redirect);
	return (errno);
}
