#include "../minishell.h"

static void	check_infile(char *infile)
{
	if (access(infile, R_OK))
	{
		syntax_error(errno, infile);
		errno = 2;
	}
}

static void	open_others(t_shell *shell, char **redir, bool has_heredoc)
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

static	pid_t	heredoc_forking(t_shell *shell, char **redir)
{
	pid_t	pid;
	int		here_pipe[2];
	int		i;

	pipe(here_pipe);
	pid = fork();
	if (pid == 0)
	{
		i = 0;
		while (redir[i] && errno != ENOMEM)
		{
			if (!ft_strncmp(redir[i], "<<", 2))
			{
				close(here_pipe[0]);
				// set_output(shell, here_pipe[1]);
				here_doc(shell, redir[i] + skip_redir_ws(redir[i]), here_pipe[1]);
			}
			++i;
		}
	}
	else
	{
		close(here_pipe[1]);
		set_input(shell, here_pipe[0]);
	}
}

int	open_files(t_shell *shell, char **redir)
{
	pid_t	pid;
	bool	has_heredoc;
	int		i;

	if (redir == NULL)
		return ;
	errno = 0;
	has_heredoc = false;
	i = 0;
	while (redir[i] && has_heredoc == false)
	{
		if (!ft_strncmp(redir[i], "<<", 2))
			has_heredoc = true;
		++i;
	}
	pid = heredoc_forking(shell, redir);
	open_others(shell, redir, has_heredoc);
	return (zombie_prevention_protocol(pid));
}
