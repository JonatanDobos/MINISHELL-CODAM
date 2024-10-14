#include "../minishell.h"

// Frees pointer array of given size, ignors NULL pointers
void	free_array_size(void **array, size_t size)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (i < size)
	{
		if (array[i])
			free(array[i++]);
	}
	free(array);
}

// size = full size of array (potential terminator included!)
void	null_set_pointerarray(void **array, size_t size)
{
	size_t	i;

	i = 0;
	while (i <= size)
		array[i++] = NULL;
}
