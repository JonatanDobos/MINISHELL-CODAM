#include "../minishell.h"

// RETURN: head of the new cmd_list, NULL if failure
t_list	**va_list_cmd_node(size_t amount, ...)
{
	va_list		cmds;
	size_t		i;
	t_list		**element_head;
	t_list		*cmd_node;

	va_start(cmds, amount);
	i = -1;
	while (++i < amount)
	{
		cmd_node = ft_lstnew(va_arg(cmds, char *));
		if (i == 0)
			element_head = &cmd_node;
		if (!cmd_node)
			return (ft_lstclear(element_head, free), NULL);
		if (i > 0)
			ft_lstadd_back(element_head, cmd_node);
	}
	va_end(cmds);
	return (element_head);
}
