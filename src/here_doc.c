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

static void	write_out(t_shell *shell, char *heredoc, int *pipe)
{
	if (!pipe)
		ft_putstr_fd(heredoc, STDIN_FILENO);
	else
	{
		set_input(shell, pipe[0]);
		set_output(shell, pipe[1]);
		ft_putstr_fd(heredoc, STDIN_FILENO);
	}
	ft_free_null(&heredoc);
	close(pipe[0]);
}

void	builtin_heredoc(t_shell *shell, char *delim, int *standup, int *pipe)
{
	char	*line;
	char	*heredoc;

	heredoc = NULL;
	printf("WERKT NOG NIET, GEZEIK MET FDS en dup2\n");
	// if (pipe)
	// 	printf("pipe[0]: %d, pipe[1]: %d\n", pipe[0], pipe[1]);
	// printf("std[0]: %d, std[1]: %d\n", standup[0], standup[1]);
	set_input(shell, standup[0]);
	set_output(shell, standup[1]);
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
	write_out(shell, heredoc, pipe);
	close(standup[0]);
}
