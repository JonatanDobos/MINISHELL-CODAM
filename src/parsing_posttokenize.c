/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_posttokenize.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 18:47:48 by svan-hoo      #+#    #+#                 */
/*   Updated: 2024/12/12 18:21:29 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Deletes all relevant quotes in a string
void	delete_quotes(char *str)
{
	size_t	i;
	size_t	skip;
	int		quote;

	i = 0;
	skip = 0;
	quote = false;
	while (str[skip])
	{
		if (!quote && (str[skip] == '\'' || str[skip] == '\"'))
		{
			quote = str[skip];
			++skip;
		}
		else if (quote && str[skip] == quote)
		{
			quote = false;
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
	quote = false;
	i = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '\"') && !quote)
			quote = line[i];
		else if (line[i] == quote)
			quote = false;
		else if (line[i] == '$' && quote != '\'')
		{
			line = insert_envp_in_str(shell, line, i);
			if (!line)
				exit_clean(shell, errno, "format_element_str()");
		}
		++i;
	}
	delete_quotes(line);
	*cmd = line;
}

// This funct formats all cmd_arrays in all tokens!
void	parse_post(t_shell *shell)
{
	size_t	i;
	t_token	*tmp;

	tmp = shell->token_head;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd_array && tmp->cmd_array[i])
		{
			format_element_str(shell, &tmp->cmd_array[i]);
			++i;
		}
		i = 0;
		if (tmp->redirect)
		{
			while (tmp->redirect[i])
			{
				format_element_str(shell, &tmp->redirect[i]);
				++i;
			}
		}
		tmp = tmp->next;
	}
}
