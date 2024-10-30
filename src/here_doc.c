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
	size_t	bytes_written;

	bytes_written = 0;
	while (1)
	{
		line = read_next_line();
		if (!line)
			return (EXIT_FAILURE);
		if (!ft_strncmp(delim, "\n", 2))//late?
			break ;
		if (!ft_strncmp(line, delim, ft_strlen(delim)))
			break ;
		line = expand_in_line(shell, line);
		if (!line)
			return (EXIT_FAILURE);
		bytes_written += write(fd_out, line, ft_strlen_null(line));
		// write(STDERR_FILENO, line, ft_strlen_null(line));
		ft_free_null(&line);
	}
	ft_free_null(&line);
	// if (bytes_written == 0)
	// 	write(fd_out, "\0", 1);
	return (EXIT_SUCCESS);
}