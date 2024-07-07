#include "../minishell.h"

// Parses for envariable corresponding to envkey.
// RETURN: shell->envp[corresponding index] (non malloced char *)
char	*parse_envp(
	t_shell *shell, size_t i)
{
	size_t	start;
	size_t	len;
	size_t	j;

	if (shell->line[i] != '$' || !ft_isalnum(shell->line[i + 1]))
		return (NULL);
	start = ++i;
	while (shell->line[i] && (shell->line[i] == '_' || \
	ft_isalnum(shell->line[i])))
		++i;
	len = i - start;
	j = 0;
	while (shell->envp[j] != NULL)
	{
		if (!ft_strncmp(shell->line + start, shell->envp[j], len))
			break ;
		++j;
	}
	if (shell->envp[j] == NULL)
		return (NULL);
	return (shell->envp[j]);
}
