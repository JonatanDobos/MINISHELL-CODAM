/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_export_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:02:04 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/06/27 21:58:41 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	export_new_key(
	t_shell *shell, char *envar)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (shell->envp[i] != NULL)
		i++;
	new_envp = ft_realloc_array(shell->envp, i + 1);
	if (new_envp == NULL)
		exit_clean(shell, errno, NULL);
	new_envp[i] = ft_strdup(envar);
	if (new_envp[i] == NULL)
		exit_clean(shell, errno, NULL);
	free(shell->envp);
	shell->envp = new_envp;
}

static void	export_update_key(
	t_shell *shell, char *envar, int i)
{
	free(shell->envp[i]);
	shell->envp[i] = ft_strdup(envar);
	if (shell->envp[i] == NULL)
		exit_clean(shell, errno, NULL);
}

// envar should be cmd_node->content, will not be free'd in this function
void	builtin_export(
	t_shell *shell, char *envar)
{
	char	*key;
	int		keylen;
	int		i;

	key = ft_strdup_d(envar, '=');
	if (key == NULL)
		exit_clean(shell, errno, NULL);
	keylen = ft_str_toupper(key); // maybe swap with strlen, do syntax check elsewhere
	i = 0;
	while (shell->envp[i] && strncmp(shell->envp[i], key, keylen))
		i++;
	if (shell->envp[i] == NULL)
		export_new_key(shell, envar);
	else
		export_update_key(shell, envar, i);
}

void	builtin_unset(
	t_shell *shell, char *envar)
{
	char	*key;
	int		keylen;
	int		i;

	key = ft_strdup_d(envar, '=');
	if (key == NULL)
		exit_clean(shell, errno, NULL);
	keylen = ft_str_toupper(key); // maybe swap with strlen, do syntax check elsewhere
	i = 0;
	while (shell->envp[i] && strncmp(shell->envp[i], key, keylen))
		i++;
	if (shell->envp[i] == NULL)
		return ;
	free(shell->envp[i]);
	while (shell->envp[i + 1] != NULL)
	{
		shell->envp[i] = shell->envp[i + 1];
		i++;
	}
	shell->envp[i] = NULL;
}
