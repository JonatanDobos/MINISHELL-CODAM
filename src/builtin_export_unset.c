/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_unset.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:02:04 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/07 19:45:21 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	export_new_key(
	t_shell *shell, const char *envar)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (shell->envp[i] != NULL)
		i++;
	new_envp = ft_realloc_array(shell->envp, i + 1);
	if (new_envp == NULL)
		exit_clean(shell, errno, NULL);
	shell->envp = new_envp;
	shell->envp[i] = ft_strdup(envar);
	if (new_envp[i] == NULL)
		exit_clean(shell, errno, NULL);
}

static void	export_update_key(
	t_shell *shell, const char *envar, int i)
{
	free(shell->envp[i]);
	shell->envp[i] = ft_strdup(envar);
	if (shell->envp[i] == NULL)
		exit_clean(shell, errno, NULL);
}

// envar should be cmd_node->content, will not be free'd in this function
void	builtin_export(
	t_shell *shell, t_token *token)
{
	char	*envar;
	char	*key;
	int		keylen;
	int		i;

	if (syntax_export(token) == false)
		return (syntax_error());
	envar = token->element_head->next->content;
	key = ft_strdup_d(envar, '=');
	if (key == NULL)
		exit_clean(shell, errno, NULL);
	i = 0;
	keylen = ft_strlen(key);
	while (shell->envp[i] && ft_strncmp(shell->envp[i], key, keylen))
		i++;
	if (shell->envp[i] == NULL)
		export_new_key(shell, envar);
	else
		export_update_key(shell, envar, i);
}

void	builtin_unset(
	t_shell *shell, t_token *token)
{
	char	*envar;
	char	*key;
	int		keylen;
	int		i;

	if (syntax_unset(token) == false)
		return (syntax_error());
	envar = token->element_head->next->content;
	key = ft_strdup_d(envar, '=');
	if (key == NULL)
		exit_clean(shell, errno, NULL);
	i = 0;
	keylen = ft_strlen(key);
	while (shell->envp[i] && ft_strncmp(shell->envp[i], key, keylen))
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
