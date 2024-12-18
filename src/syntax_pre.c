/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_pre.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 18:48:08 by svan-hoo      #+#    #+#                 */
/*   Updated: 2024/12/12 15:08:25 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	quote_check(const char *line)
{
	char	quote;
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				++i;
			if (line[i] != quote)
				return (false);
		}
		++i;
	}
	return (true);
}

static bool	pipe_exception(const char *line)
{
	size_t	i;
	size_t	token_count;

	i = 0;
	while (istoken(line[i]))
		++i;
	token_count = i;
	if (token_count > 1)
		return (print_token_err(&line[1], 1), false);
	while (ft_iswhitespace(line[i]))
		++i;
	if (!line[i] || istoken(line[i]))
		return (print_token_err(&line[i], 1), false);
	return (true);
}

static bool	check_token_folowup(const char *line)
{
	size_t	i;
	size_t	token_count;

	i = 0;
	while (istoken(line[i]))
		++i;
	token_count = i;
	if (token_count > 2)
		return (print_token_err(&line[2], 1), false);
	else if (token_count == 2 && istoken(line[1]) && (line[0] - line[1]))
		return (print_token_err(&line[1], 1), false);
	while (ft_iswhitespace(line[i]))
		++i;
	if (!line[i] || (istoken(line[i]) && token_count == 2))
		return (print_token_err(&line[i], 1), false);
	if (istoken(line[i]) && (line[0] - line[i]))
		return (print_token_err(&line[i], 1), false);
	token_count = i;
	if (istoken(line[i]))
		++i;
	while (ft_iswhitespace(line[i]))
		++i;
	if (token_count < i && istoken(line[i]))
		return (print_token_err(&line[i], 1), false);
	return (true);
}

static bool	token_check(const char *line)
{
	size_t	i;

	if (pipe_start(line) == true)
		return (print_token_err("|", 1), false);
	i = 0;
	while (line[i])
	{
		if (istoken(line[i]))
		{
			if (line[i] == '|')
			{
				if (pipe_exception(line + i) == false)
					return (false);
			}
			if (check_token_folowup(line + i) == false)
				return (false);
			while (istoken(line[i]))
				++i;
		}
		if (line[i] == '\'' || line[i] == '\"')
			i = skip_to_next_quote(line, i);
		++i;
	}
	return (true);
}

bool	syntax_pre(t_shell *shell, const char *line)
{
	if (!quote_check(line))
	{
		ft_putstr_fd("minishell: Function not implemented\n", STDERR_FILENO);
		shell->last_errno = EINVAL;
		return (false);
	}
	if (!token_check(line))
	{
		shell->last_errno = EINVAL;
		return (false);
	}
	return (true);
}
