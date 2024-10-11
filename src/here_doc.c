#include "../minishell.h"

// SHOULD IMPLEMENT PIPE!!!!!!

// IMPLEMENT: should react to signals!
// On failure shell_heredoc is freed in exit clean
void	here_doc(t_shell *shell, char *delim)
{
	char	*line;
	char	*dup_line;

	ft_free_array(shell->heredoc);
	shell->heredoc = NULL;
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line_heredoc(STDIN_FILENO);
		if (!line)
			exit_clean(shell, errno, "here_doc: malloc failure");
		if (!ft_strncmp(line, delim, ft_strlen(delim)))
			break ;
		dup_line = ft_strdup(line);
		ft_free_null(&line);
		if (!dup_line)
			exit_clean(shell, errno, "here_doc: malloc failure");
		shell->heredoc = ft_array_append(shell->heredoc, dup_line);
		if (!shell->heredoc)
			exit_clean(shell, errno, "here_doc: malloc failure");
	}
	ft_free_null(&line);
	here_doc_test(shell);
	// TEST_print_pointer_arr(shell->heredoc, NULL, C_BLUE, true, C_BLUE, "Here_doc check");// TEST
}
