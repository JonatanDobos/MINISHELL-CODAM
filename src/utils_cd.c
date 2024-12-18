/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_cd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 18:58:36 by jdobos        #+#    #+#                 */
/*   Updated: 2024/12/12 23:30:17 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*cd_home_append(char *home, const char *operand)
{
	char	*path;
	size_t	i;
	size_t	j;

	if (operand++ == NULL || home == NULL)
		return (NULL);
	home = ft_strdup(home);
	if (home == NULL)
		return (NULL);
	if (operand[0] != '/' && ft_strchr(home, '/') != ft_strrchr(home, '/'))
		*(ft_strrchr(home, '/') + 1) = '\0';
	path = (char *)malloc(ft_strlen((char *)operand) + ft_strlen(home) + 1);
	if (path == NULL)
		return (free(home), NULL);
	i = 0;
	j = 0;
	while (home[j])
		path[i++] = home[j++];
	j = 0;
	while (operand[j])
		path[i++] = operand[j++];
	path[i] = '\0';
	free(home);
	return (path);
}

bool	cd_set_operand(char **cmd_array, char **operand)
{
	size_t	i;

	i = 1;
	while (cmd_array[i] && cmd_array[i][0] == '\0')
		++i;
	*operand = cmd_array[i];
	if (cmd_array[i] == NULL || cmd_array[i + 1] == NULL)
		return (true);
	++i;
	while (cmd_array[i] && cmd_array[i][0] == '\0')
		++i;
	if (cmd_array[i] == NULL)
		return (true);
	else
		return (false);
}
