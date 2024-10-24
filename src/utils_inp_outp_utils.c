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

bool	check_for_heredoc(char **redirects)
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
