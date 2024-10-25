#include "../minishell.h"

void	check_infile(char *infile)
{
	if (access(infile, R_OK))
	{
		syntax_error(errno, infile);
		errno = 2;
	}
}

void	save_standard_fds(t_shell *shell, int *standup)
{
	standup[0] = dup(STDIN_FILENO);
	if (standup[0] < 0)
		exit_clean(shell, errno, "standup[0]");
	standup[1] = dup(STDOUT_FILENO);
	if (standup[1] < 0)
		exit_clean(shell, errno, "standup[1]");
}

void	reset_fds(t_shell *shell, int *standup)
{
	set_input(shell, standup[0]);
	set_output(shell, standup[1]);
}

// closes fd and sets value to -1
// (to prevent use after close)
int	close_fd(int *fd)
{
	if (fd >= 0)
	{
		if (close(*fd) == -1)
			return (-1);
		*fd = -1;
	}
	else
		ft_putendl_fd("fd = -1", STDERR_FILENO);//test
	return (0);
}

bool	check_for_heredoc(char **redirects)
{
	int	i;

	i = 0;
	while (redirects && redirects[i])
	{
		if (!ft_strncmp(redirects[i], "<<", 2))
			return (true);
		++i;
	}
	return (false);
}
