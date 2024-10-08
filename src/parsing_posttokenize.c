#include "../minishell.h"

// Deletes all relevant quotes in a string
void	delete_quotes(char *str)
{
	size_t	i;
	size_t	skip;
	int		quote;

	i = 0;
	skip = 0;
	quote = 0;
	while (str[skip])
	{
		if (!quote && (str[skip] == '\'' || str[skip] == '\"'))
		{
			quote = str[skip];
			++skip;
		}
		else if (quote && str[skip] == quote)
		{
			quote = 0;
			++skip;
		}
		else
			str[i++] = str[skip++];
	}
	str[i] = '\0';
}

// Checks for quotes and expandables
// Exits inside when malloc fail
void	format_element_str(t_shell *shell, char **cmd)
{
	char	*line;
	char	quote;
	size_t	i;

	line = *cmd;
	quote = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			quote = line[i];
		else if (line[i] == quote)
			quote = 0;
		else if (line[i] == '$' && quote != '\'')
		{
			line = insert_envp_in_str(shell, line, i);
			if (!line)
				exit_clean(shell, errno, "50: check_cmd(): malloc fail");
		}
		++i;
	}
	delete_quotes(line);
	*cmd = line;
}

void	parse_post(t_shell *shell)
{
	size_t	i;
	t_token	*tmp;

	tmp = shell->token_head;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd_array[i])
		{
			format_element_str(shell, &tmp->cmd_array[i]);
			++i;
		}
		tmp = tmp->next;
	}
}
