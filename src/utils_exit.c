#include "../minishell.h"

// attempts to free everything known to shell, then exits
void	exit_clean(t_shell *shell, int num, char *message)
{
	clean_lists(shell);
	ft_free_array(shell->envp);
	ft_free_null(&shell->history);
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

// used by children
void	error_exit(int num, char *param)
{
	const char	*nill = "\0";

	if (num != errno)
		errno = num;
	if (param == NULL)
		param = (char *)nill;
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (errno == 127)
		printf("minishell: command not found: %s\n", param);
	else
		printf("minishell: %s: %s\n", strerror(errno), param);
	exit(errno);
}
