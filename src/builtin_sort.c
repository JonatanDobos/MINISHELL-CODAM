#include "../minishell.h"

static bool	relevant_is_lower(short relevant, short compared_to)
{
	if ((compared_to == '=' || compared_to == '\0')
	|| (ft_islower(compared_to) && ft_isupper(relevant))
	|| (!ft_isalpha(relevant) && ft_isupper(compared_to))
	|| (!ft_isalpha(compared_to) && ft_islower(relevant)))
		return (true);
	return (false);
}

static bool	relevant_is_higher(short relevant, short compared_to)
{
	if ((relevant == '=' || relevant == '\0')
	|| (ft_isupper(compared_to) && ft_islower(relevant))
	|| (ft_isupper(relevant) && !ft_isalpha(compared_to))
	|| (ft_islower(compared_to) && !ft_isalpha(relevant)))
		return (true);
	return (false);
}

static short	cmp_sort(char *relevant, char *compared_to)
{
	size_t	i;
	size_t	r;
	size_t	c;

	i = 0;
	r = 0;
	c = 0;
	while ((relevant[i + r] && (relevant[i + r] == compared_to[i + c])
	|| !ft_isalpha(relevant[i + r]) || !ft_isalpha(compared_to[i + c])))
	{
		if (relevant[i + r] && !ft_isalpha(relevant[i + r]))
			++r;
		else if (compared_to[i + c] && !ft_isalpha(compared_to[i + c]))
			++c;
		else
			++i;
	}
	if ((relevant[i + r] == '=' || relevant[i + r] == '\0')
	&& (compared_to[i + c] == '=' || compared_to[i + c] == '\0'))
		return (r - c);
	if (relevant_is_lower(relevant[i + r], compared_to[i + c]))
		return (1);
	if (relevant_is_higher(relevant[i + r], compared_to[i + c]))
		return (-1);
	return (relevant[i + r] - compared_to[i + c]);
}

static void	sorting(char **array)
{
	size_t	i;
	size_t	size;
	bool	sorted;

	size = 0;
	while (array[size] != NULL)
		++size;
	sorted = false;
	while (sorted == false)
	{
		sorted = true;
		i = 0;
		while (i < size)
		{
			if (i == size -1 && cmp_sort(array[0], array[i]) > 0
			|| (i < size - 1 && cmp_sort(array[i], array[i + 1]) > 0))
			{
				ptr_switch(&array[i], &array[i + 1]);
				sorted = false;
			}
			++i;
		}
	}
}

static void	print_sorted_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		ft_putstr(array[i++]);
		ft_putstr("\n");
	}
}

// UNTESTED! not implemented yet in execution!
// Maybe change to (int fd) input for pipes and files (jusst like real sort)
int	builtin_sort(char **array)
{
	char	**new_array;
	size_t	size;

	if (!array || !(*array))
		return (EXIT_FAILURE);
	while (array[size])
		++size;
	new_array = (char **)malloc(sizeof(char *) * size);
	if (!new_array)
		return (errno);
	new_array[size] = NULL;
	size = 0;
	while (new_array[size])
	{
		new_array[size] = array[size];
		++size;
	}
	sorting(new_array);
	print_sorted_array(new_array);
	return (EXIT_SUCCESS);
}
