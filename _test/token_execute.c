#include "../minishell.h"

bool	isend_of_word(char c)
{
	return (ft_iswhitespace(c) || c == '\0');
}

// Returns: skip amount
static size_t	elem_execute(t_shell *shell, char *line)
{
	if (ft_strncmp(line, "cd", 2) && isend_of_word(line + 2))
		return (builtin_cd())// LEFTOFF!!
}

void	token_execute(t_shell *shell)
{
	t_list	*tmp;
	
	tmp = shell->line_element_head;
	while (tmp)
	{
		
		tmp = tmp->next;
	}
}
