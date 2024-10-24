#include "../minishell.h"

// Expands envp inside string
// *str freed inside function
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
			str = insert_envp_in_str(shell, str, i);
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

	if (!add)
		return (NULL);
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

char	*builtin_heredoc(t_shell *shell, char *delim)
{
	char	*line;
	char	*inp;

	inp = NULL;
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line_heredoc(STDIN_FILENO);
		if (!line)
			return (ft_free_null(&inp), NULL);
		if (!ft_strncmp(line, delim, ft_strlen(delim)))
			break ;
		inp = line_append(inp, expand_in_line(shell, line));
		if (!inp)
			return (ft_free_null(&line), NULL);
		if (!ft_strncmp(delim, "\n", 2))
			break ;
		ft_free_null(&line);
	}
	ft_free_null(&line);
	return (inp);
}
