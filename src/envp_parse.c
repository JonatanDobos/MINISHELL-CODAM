#include "../minishell.h"

// There should be a universal function for this
static void	add_to_arglist(t_shell *shell, char *str, size_t len)
{
	char		*var;
	t_list		*new_list;
	t_token		*new_sig;

	var = ft_substr(str, len, ft_strlen(str) - len);
	if (!var)
		exit_clean(shell, errno, NULL);
	new_list = ft_lstnew(var);
	if (!new_list)
	{
		free(var);
		exit_clean(shell, errno, NULL);
	}
	new_sig = sig_arg_new(&new_list, NULL, T_BUILTIN);
	if (!new_sig)
	{
		ft_lstdelone(new_list, free);
		exit_clean(shell, errno, NULL);
	}
	sig_arg_add_back(shell->sig_arg_head, new_sig);
}

// Parses for envariable corresponding to envkey, if found:
// Inputs envariable into node 0 of cmd_node
// RETURN: incremented index on line
size_t	parse_envp(
	t_shell *shell, size_t i)
{
	size_t		start;
	size_t		len;
	size_t		j;

	if (shell->line[i] != '$' || !ft_isalnum(shell->line[i + 1]))
		return (i);
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
		return (i); // not found ? what should it do
	add_to_arglist(shell, shell->envp[j], len);
	return (i);
}
