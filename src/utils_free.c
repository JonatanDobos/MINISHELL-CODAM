#include "../minishell.h"

// Frees variable amount of pointers (if != NULL)
void	free_va(int amount, ...)
{
	va_list	ptrs_to_free;
	short	i;

	va_start(ptrs_to_free, amount);
	i = 0;
	while (i < amount)
	{
		free(va_arg(ptrs_to_free, void *));
		++i;
	}
	va_end(ptrs_to_free);
}

void	clean_lists(t_shell *shell)
{
	token_clear(&shell->token_head);
	ft_lstclear(&shell->line_element_head, free);
	ft_free_null(&shell->line);
	shell->token_head = NULL;
	shell->line_element_head = NULL;
}
