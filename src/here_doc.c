#include "../minishell.h"

// IMPLEMENT: should react to signals!
bool	here_doc(t_shell *shell, char *delim, int fd)
{
	char	*line;

	while (1)
	{
		rl_on_new_line();
		line = readline("> ");
		if (!line)
			return (false);
		if (ft_strncmp(line, delim, ft_strlen(line)))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		ft_free_null(&line);
	}
	free(line);
	return (true);
}
