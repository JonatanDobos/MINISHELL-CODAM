/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:46:11 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/08 18:46:18 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_unset(char *envar, char **envp)
{
	char		*key;
	int			i;

	if (envar == NULL)
		return (EXIT_SUCCESS);
	if (unset_syntax(envar) == false)
		return (unset_error(envar), EXIT_FAILURE);
	if (ft_strchr(envar, '='))
		key = ft_strdup_d(envar, '=');
	else
		key = ft_strdup(envar);
	if (key == NULL)
		return (errno);
	i = envp_key_index(envp, key);
	if (envp[i] == NULL)
		return (free(key), EXIT_SUCCESS);
	free(envp[i]);
	while (envp[i + 1] != NULL)
	{
		envp[i] = envp[i + 1];
		i++;
	}
	envp[i] = NULL;
	return (EXIT_SUCCESS);
}

static int	export_new_key(const char *envar, char ***envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	while ((*envp)[i] != NULL)
		i++;
	new_envp = ft_realloc_array(*envp, i + 1);
	if (new_envp == NULL)
		return (errno);
	new_envp[i] = ft_strdup(envar);
	if (new_envp[i] == NULL)
		return (errno);
	*envp = new_envp;
	return (EXIT_SUCCESS);
}

static int	export_update_key(const char *envar, int i, char **envp)
{
	free(envp[i]);
	envp[i] = ft_strdup(envar);
	if (envp[i] == NULL)
		return (errno);
	return (EXIT_SUCCESS);
}

int	builtin_export(char *envar, char ***envp, char ***sorted)
{
	char	*key;
	int		i;
	short	exit_code;

	exit_code = export_envar_to_sorted_array(envar, sorted);
	if (exit_code == EXIT_FAILURE)
		return (export_error(envar), EXIT_FAILURE);
	if (exit_code)
		return (exit_code);
	if (export_syntax(envar) == false)
		return (EXIT_SUCCESS);
	key = ft_strdup_d(envar, '=');
	if (key == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while ((*envp)[i] && ft_strncmp((*envp)[i], key, ft_strlen(key)))
		i++;
	exit_code = EXIT_SUCCESS;
	if ((*envp)[i] == NULL)
		exit_code = export_new_key(envar, envp);
	else
		exit_code = export_update_key(envar, i, *envp);
	free(key);
	return (exit_code);
}
