/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_builtin.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 18:48:16 by svan-hoo      #+#    #+#                 */
/*   Updated: 2024/11/25 18:18:19 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// replicates bash's syntax for valid envp KEYs/identifiers
int	export_syntax(const char *envar)
{
	int	i;

	if (envar == NULL || !envar[0])
		return (false);
	i = 0;
	if (!ft_isalpha(envar[i]) && envar[i] != '_')
		return (false);
	++i;
	while (envar[i] && envar[i] != '=')
	{
		if (!ft_isalnum(envar[i]) && envar[i] != '_')
			return (false);
		++i;
	}
	if (i <= 1)
		return (false);
	if (envar[i] != '=')
		return (false);
	return (true);
}

int	unset_syntax(const char *envar)
{
	int	i;

	i = 0;
	if (!ft_isalpha(envar[i]) && envar[i] != '_')
		return (false);
	++i;
	while (envar[i] && envar[i] != '=')
	{
		if (!ft_isalnum(envar[i]) && envar[i] != '_')
			return (false);
		++i;
	}
	if (envar[i] == '=')
		return (false);
	return (true);
}

// points to the value behind given kye inside envp, not malloc'd
char	*get_env(char **envp, const char *key)
{
	int		i;
	char	*ret;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], key, ft_strlen(key)))
		++i;
	ret = envp[i];
	if (ret != NULL)
		while (*ret++ != '=')
			;
	return (ret);
}

// Prints the sorted envp list
int	print_export_list(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

bool	echo_n_flag_check(char *str)
{
	int	i;

	if (str == NULL)
		return (false);
	if (str[0] != '-')
		return (false);
	if (str[1] != 'n')
		return (false);
	i = 2;
	while (str[i] == 'n')
		++i;
	if (str[i] == '\0')
		return (true);
	return (false);
}
