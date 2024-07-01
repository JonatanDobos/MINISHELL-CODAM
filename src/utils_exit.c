#include "../minishell.h"

// attempts to free everything known to shell, then exits
void	exit_clean(t_shell *shell, int num, char *message)
{
	free_arglist(shell->sig_arg_head);
	ft_free_null(&shell->line);
	ft_free_array(shell->history);
	ft_free_array(shell->envp);
	rl_clear_history();
	errno = num;
	if (num != SUCCESS)
		perror(message);
	exit(num);
}

// (EXPERIMENTAL)
// Exits the program with exit_clean() after freeing variable amount of pointers
// void	exit_va_free(t_shell *shell, int num, char *message, int amount, ...)
// {
// 	va_list	ptrs_to_free;
// 	int		i;

// 	va_start(ptrs_to_free, amount);
// 	i = 0;
// 	while (i < amount)
// 	{
// 		free_if(va_arg(ptrs_to_free, void *));
// 		++i;
// 	}
// 	va_end(ptrs_to_free);
// 	exit_clean(shell, num, message);
// }
