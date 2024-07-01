#include "../minishell.h"

// Frees *ptr if != NULL, then sets it to NULL
void	free_setnull(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

// Frees variable amount of pointers (if != NULL)
void	free_va(int amount, ...)
{
	va_list	ptrs_to_free;
	short	i;

	va_start(ptrs_to_free, amount);
	i = 0;
	while (i < amount)
	{
		free_if(va_arg(ptrs_to_free, void *));
		++i;
	}
	va_end(ptrs_to_free);
}
