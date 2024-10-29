#include "../minishell.h"

static void	determine_output(t_shell *shell, t_list *next, t_fds *fds)
{
	if (next == NULL)
	{
		set_output(shell, fds->stdup[1]);
		if (close_fd(&fds->pipe[1]) == -1)
			exit_clean(shell, errno, "determine_output()");
	}
	else
	{
		set_output(shell, fds->pipe[1]);
		if (close_fd(&fds->stdup[1]) == -1)
			exit_clean(shell, errno, "determine_output()");
	}
}

void	open_files(t_shell *shell, char **redir, bool has_heredoc)
{
	int	i;

	i = 0;
	while (redir && redir[i] && !errno)
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
	char		*inp;
	int			i;

	if (redir == NULL)
		return ;
	i = 0;
	inp = NULL;
	set_input(shell, standup[0]);
	while (redir[i])
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
	close(STDIN_FILENO);// ?
}

int	heredoc_fork(t_shell *shell, char **redir, t_fds *fds, bool type)
{
	pid_t	pid;
	int		status;
	
	pid = fork();
	if (pid == -1)
		return (errno);
	if (pid == 0)
	{
		errno = 0;
		if (type == HERE_DOC)
			open_heredocs(shell, redir, fds->stdup);
		else if (type == HERE_DUMMY)
			open_dummy_heredocs(shell, redir);
		//all fds closed?
		exit_clean(shell, errno, NULL);
	}
	return (zombie_prevention_protocol(pid));
}

int	inp_outp_manager(t_shell *shell, t_token *token, t_fds *fds)
{
	const bool	has_heredoc = check_for_heredoc(token->redirect);

	errno = 0;
	if (close_fd(&fds->pipe[0]) ==  -1)
		return (errno);
	if (close_fd(&fds->stdup[0]) == -1)
		return (errno);
	determine_output(shell, token->next, fds);
	if (token->redirect)
		open_files(shell, token->redirect, has_heredoc);
	return (errno);
}

void	open_dummy_heredocs(t_shell *shell, char **redir)
{
	char		*inp;
	int			i;

	if (redir == NULL)
		return ;
	i = 0;
	inp = NULL;
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
	ft_free_null(&inp);
}