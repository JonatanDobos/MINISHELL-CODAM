#include "../minishell.h"

void	builtin_echo(t_shell *shell, char **cmd_array)
{
	int	i;

	i = 1;
	while (cmd_array[i])
	{
		printf("%s", cmd_array[i]);
		++i;
	}
	printf("\n");
}
