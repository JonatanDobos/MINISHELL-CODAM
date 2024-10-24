#include "../minishell.h"

static void	determine_output(t_shell *shell,
	t_list *next, int *standup, int *pipe_fds)
{
	if (next == NULL)
	{
		set_output(shell, standup[1]);
		if (close(pipe_fds[1]) == -1)
			exit_clean(shell, errno, "determine_output()");
	}
	else
	{
		set_output(shell, pipe_fds[1]);
		if (close(standup[1]) == -1)
			exit_clean(shell, errno, "determine_output()");
	}
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

void	open_heredocs(t_shell *shell, char **redir, int *standup)
{
	bool		has_heredoc;
	char		*inp;
	int			i;

	if (redir == NULL)
		return ;
	i = 0;
	inp = NULL;
	set_input(shell, standup[0]);
	while (redir[i] && errno != ENOMEM)
	{
		
		if (!ft_strncmp(redir[i], "<<", 2))
		{
			ft_free_null(&inp);
			inp = builtin_heredoc(shell, redir[i] + skip_redir_ws(redir[i]));
			if (inp == NULL)
				exit_clean(shell, errno, "builtin_heredoc()");
		}
		++i;
	}
	ft_putstr_fd(inp, STDIN_FILENO);
	ft_free_null(&inp);
	close(STDIN_FILENO);
}

int	inp_outp_manager(t_shell *shell, t_token *token, int *standup, int *pipe)
{
	errno = 0;
	determine_output(shell, token->next, standup, pipe);
	if (token->redirect)
		open_files(shell, token->redirect);
	if (token->redirect && check_for_heredoc(token->redirect))
		open_heredocs(shell, token->redirect, standup);
	if (errno)
		return (errno);
	if (close(pipe[0]) ==  -1)
		return (errno);
	if (close(standup[0]) == -1)
		return (errno);
	return (errno);
}
