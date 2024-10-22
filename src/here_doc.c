#include "../minishell.h"

// SHOULD IMPLEMENT PIPE!!!!!!

// IMPLEMENT: should react to signals! (make it run as child!)
// On failure shell_heredoc is freed in exit clean
static char	*line_append(char *line, char *add)
{
	size_t	i;
	size_t	j;
	char	*new;

	new = (char *)malloc(ft_strlen_null(line) + ft_strlen_null(add) + 1);
	if (!new)
		return (ft_free_null(&line), NULL);
	i = 0;
	j = 0;
	while (line && line[j])
		new[i++] = line[j++];
	j = 0;
	while (add && add[j])
		new[i++] = add[j++];
	new[i] = '\0';
	ft_free_null(&line);
	return (new);
}

void	builtin_heredoc(t_shell *shell, char *delim, int *standup)
{
	char	*line;
	char	*heredoc;

	heredoc = NULL;
	set_input(shell, standup[0]);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line_heredoc(STDIN_FILENO);
		if (!line)
			return (ft_free_null(&heredoc), exit_clean(shell, errno, "heredoc(1)"));
		if (!ft_strncmp(line, delim, ft_strlen(delim)))
			break ;
		heredoc = line_append(heredoc, line);
		if (!heredoc)
			return (ft_free_null(&line), exit_clean(shell, errno, "heredoc(2)"));
		if (!ft_strncmp(delim, "\n", 2))
			break ;
		ft_free_null(&line);
	}
	ft_free_null(&line);
	ft_putstr_fd(heredoc, STDIN_FILENO);
	close(STDIN_FILENO);
}
