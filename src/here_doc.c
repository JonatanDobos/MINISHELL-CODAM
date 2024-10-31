#include "../minishell.h"

// Expands envp inside string
// *str freed inside function
static char	*insert_env(t_shell *shell, char *str, size_t i)
{
	const char	*check = str;
	size_t		j;

	if (!str)
		return (NULL);
	str = insert_envp_in_str(shell, str, i);
	if (str == check)
	{
		j = i;
		while (!ft_iswhitespace(str[j]))
			++j;
		str = str_insert(str, "", i, j - i);
	}
	return (str);
}

static char	*expand_in_line(t_shell *shell, char *str)
{
	size_t	i;
	bool	double_quote;

	i = 0;
	double_quote = false;
	while (str[i])
	{
		if (str[i] == '\"' && double_quote == true)
			double_quote = false;
		else if (str[i] == '\"' && double_quote == false)
			double_quote = true;
		else if (str[i] == '\'' && double_quote == false)
			i = skip_to_next_quote(str, i);
		else if (str[i] == '$')
		{
			str = insert_env(shell, str, i);
			if (!str)
				return (NULL);
		}
		++i;
	}
	return (str);
}

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

static char	*read_next_line(void)
{
	char	*line;

	write(STDOUT_FILENO, "> ", 2);
	// sig_child();
	fprintf(stderr, "\nreading heredoc...\n");
	line = get_next_line_heredoc(STDIN_FILENO);
	// sig_noninteractive();
	if (!line)
		return (NULL);
	fprintf(stderr, "\nread from heredoc: %s\n", line);
	return (line);
}

int	here_doc(t_shell *shell, char *delim, int fd_out)
{
	char	*line;

	while (1)
	{
		line = read_next_line();
		if (!line)
		if (!ft_strncmp(line, delim, ft_strlen(delim)))
			break ;
		line = expand_in_line(shell, line);
		if (!line)
			return (EXIT_FAILURE);
		ft_putendl_fd(line, fd_out);
		// write(STDERR_FILENO, line, ft_strlen_null(line));
			return (EXIT_FAILURE);
		if (!ft_strncmp(delim, "\n", 2))
			break ;
		ft_free_null(&line);
	}
	ft_free_null(&line);
	return (EXIT_SUCCESS);
}

static void	close_heredoc_pipes(t_token *token)
{
	if (token->heredoc_pipe[0] != -1 && close(token->heredoc_pipe[0]) == -1)
		perror("token->heredoc_pipe[0]");
	if (token->heredoc_pipe[1] != -1 && close(token->heredoc_pipe[1]) == -1)
		perror("token->heredoc_pipe[1]");
	token->heredoc_pipe[0] = -1;
	token->heredoc_pipe[1] = -1;
}

static void	run_heredoc(t_shell *shell, t_token *token, char *delimiter)
{
	char	*input;
	int		limiter_len;

	rl_clear_history();
	limiter_len = ft_strlen(delimiter);
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
		{
			write_heredoc_error(delimiter);
			break ;
		}
		if (ft_strncmp(input, delimiter, limiter_len) == 0
			&& input[limiter_len] == '\0')
		{
			free(input);
			break ;
		}
		input = add_newline(shell, input);
		write(token->heredoc_pipe[1], input, ft_strlen(input));
		free(input);
	}
	// shell->pid = 1;
	close_heredoc_pipes(token);
}

static pid_t	set_heredoc(t_shell *shell, t_token *token, char *delimiter)
{
	pid_t	hd_pid;

	close_heredoc_pipes(token);
	if (pipe(token->heredoc_pipe) == -1)
		kill_program(shell, "Failed creating pipe", errno);
	g_signal = -1;
	hd_pid = fork();
	if (hd_pid == -1)
		kill_program(shell, NULL, errno);
	if (hd_pid == 0)
	{
		init_signals(shell, 3);
		run_heredoc(shell, token, delimiter);
		kill_program(shell, NULL, 0);
	}
	if (close(token->heredoc_pipe[1]) == -1)
		perror("token->heredoc_pipe[1]");
	token->heredoc_pipe[1] = -1;
	return (hd_pid);
}

int	check_heredoc(t_shell *shell)
{
	t_ctable	*token;
	t_file		*infiles;
	pid_t		pid;
	int			status;

	token = shell->input->token;
	while (token != NULL)
	{
		infiles = token->infiles;
		while (infiles != NULL)
		{
			if (infiles->type == t_in_heredoc)
			{
				pid = set_heredoc(shell, token, infiles);
				waitpid(pid, &status, 0);
				if (WIFSIGNALED(status))
					return (130);
				else
					shell->exit_code = 0;
			}
			infiles = infiles->next;
		}
		token = token->next;
	}
	return (0);
}

int	all_heredocs(t_shell *shell, char **redir)
{
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
	{
		pid = heredoc_forking(shell, redir);
		open_others(shell, redir, has_heredoc);
		return (zombie_prevention_protocol(pid));
	}
	return (errno);
}
