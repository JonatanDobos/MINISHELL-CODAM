#include "../minishell.h"

static void	check_infile(const char *infile)
{
	if (access(infile, R_OK))
	{
		syntax_error(errno, infile);
		errno = 2;
	}
}

static void	open_others(t_shell *shell, const char **redir, bool has_heredoc)
{
	int	i;

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

int	open_files(t_shell *shell, t_token *token)
{
	const	char **redir = token->redirect;
	pid_t	pid;
	bool	has_heredoc;
	int		i;

	if (redir == NULL)
		return (EXIT_SUCCESS);
	errno = 0;
	has_heredoc = false;
	i = 0;
	while (redir[i] && has_heredoc == false)
	{
		if (!ft_strncmp(redir[i], "<<", 2))
			has_heredoc = true;
		++i;
	}
	open_others(shell, redir, has_heredoc);
	if (has_heredoc)
		set_input(shell, token->heredoc_pipe[0]);
	return (errno);
}
