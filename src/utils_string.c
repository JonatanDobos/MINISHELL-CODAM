/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:48:31 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/08 18:48:32 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// *str > string to read from
// start > starting index for reading from str
// end > stopping index, isn't included!
// Read part gets strdupped, return is malloced!
char	*strdup_index(char *str, size_t	start, size_t end)
{
	char	*ret;
	int		i;

	if (!str || start < 0 || end > ft_strlen(str) || end <= start)
		return (NULL);
	ret = (char *)malloc((end + 1 - start) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (start < end)
		ret[i++] = str[start++];
	ret[i] = '\0';
	return (ret);
}

// Converts all whitespace in *str to single space
// No malloc/ realloc
char	*ft_onlyspace(char *str)
{
	size_t	i;
	size_t	new;

	if (!str)
		return (NULL);
	i = 0;
	new = 0;
	while (str[i])
	{
		if (str[i] != ' ' && ft_iswhitespace(str[i]))
		{
			while (str[i] != ' ' && ft_iswhitespace(str[i]))
				++i;
			str[new++] = ' ';
		}
		else
			str[new++] = str[i++];
	}
	str[new] = '\0';
	return (str);
}

// Returns:
// - copy of *str with str[start] -> str[start + len_del] replaced by *insert
// - *str when input is incufficient
// - NULL on malloc failure
char	*str_insert(char *str, char *insert, size_t start, size_t len_del)
{
	size_t	i;
	size_t	j;
	char	*ret;

	if (!str || !insert || start > ft_strlen(str) || \
	len_del > ft_strlen_null(str) - start)
		return (str);
	ret = (char *)malloc((ft_strlen(str) - len_del) + ft_strlen(insert) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (i < start)
		ret[i++] = str[j++];
	j = 0;
	while (insert[j])
		ret[i++] = insert[j++];
	j = start + len_del;
	while (str[j])
		ret[i++] = str[j++];
	ret[i] = '\0';
	return (ret);
}

// Formats str before parsing
// - takes out unnecessary whitespace
// - not between single quotes
void	str_pre_format(char *str)
{
	bool	quote;
	size_t	new;
	size_t	i;

	i = 0;
	new = 0;
	quote = false;
	while (str[i])
	{
		if (quote == false && str[i] == '\'')
			quote = true;
		else if (quote && str[i] == '\'')
			quote = false;
		if (quote == false && str[i] != ' ' && ft_iswhitespace(str[i]))
		{
			while (str[i] != ' ' && ft_iswhitespace(str[i]))
				++i;
			str[new++] = ' ';
		}
		else
			str[new++] = str[i++];
	}
	str[new] = '\0';
}
