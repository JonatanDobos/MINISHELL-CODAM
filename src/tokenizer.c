#include "../minishell.h"

// Assigns tokens to each argument.
// Tokens defined in: minish_def.h
void	tokenizer(t_shell *shell)
{
	size_t	i;
	
	i = 0;
	while (shell->line[i])
	{
		if (shell->line[i] == ' ')
			++i;
		i = parse_envp(shell, i);
	}
}
