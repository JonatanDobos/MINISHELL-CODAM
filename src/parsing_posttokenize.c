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
void	check_cmd(t_shell *shell, char **cmd)
{
	char	*line;
	char	quote;

	line = *cmd;
	quote = 0;
	if (line[0] == '\'' || line[0] == '\"')
	{
		quote = line[0];
		delete_quotes(line);
	}
	if (quote != '\'')
	{
		*cmd = expand_env_in_str(shell, line);
		if (!(*cmd))
			exit_clean(shell, errno, "check_cmd(): malloc fail");
	}
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
			check_cmd(shell, &tmp->cmd_array[i]);
			++i;
		}
		tmp = tmp->next;
	}
}
