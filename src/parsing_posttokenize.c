#include "../minishell.h"

// // Deletes all quotes in a string
// void	delete_quotes(char *str)
// {
// 	size_t	i;
// 	size_t	skip;
// 	int		quote;

// 	i = 0;
// 	skip = 0;
// 	quote = 0;
// 	while (str[skip])
// 	{
// 		if (!quote && (str[skip] == '\'' || str[skip] == '\"'))
// 		{
// 			quote = str[skip];
// 			++skip;
// 		}
// 		else if (quote && str[skip] == quote)
// 		{
// 			quote = 0;
// 			++skip;
// 		}
// 		else
// 			str[i++] = str[skip++];
// 	}
// 	str[i] = '\0';
// }

// static void	quote_handling(t_shell *shell, char *line, size_t i)
// {
// 	char	quote;
// 	char	*sub_str;
// 	size_t	start;
// 	size_t	len;

// 	quote = line[i];
// 	start = ++i;
// 	while (line[i] != quote && line[i])
// 		++i;
// 	len = i - start;
// 	if (quote == '\'')
// 		new_element(shell, ft_substr(line, start, len));
// 	else if (quote == '\"')
// 	{
// 		sub_str = ft_onlyspace(ft_substr(line, start, len));
// 		if (!sub_str)
// 			exit_clean(shell, errno, NULL);
// 		new_element(shell, expand_env_in_str(shell, sub_str));
// 	}
// }

// void	parse_post(t_shell *shell)
// {

// }
