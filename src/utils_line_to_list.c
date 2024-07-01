#include "../minishell.h"

void	del_t_list(void *content)
{
	free(content);
}

// RETURN: head of the new cmd_list, NULL if failure
t_list	**va_list_cmd_node(
	size_t amount,
	...)
{
	va_list		cmds;
	size_t		i;
	t_list		**cmd_head;
	t_list		*cmd_node;

	va_start(cmds, amount);
	i = -1;
	while (++i < amount)
	{
		cmd_node = ft_lstnew(va_arg(cmds, char *));
		if (i == 0)
			cmd_head = &cmd_node;
		if (!cmd_node)
			return (ft_lstclear(cmd_head, del_t_list), NULL);
		if (i > 0)
			ft_lstadd_back(cmd_head, cmd_node);
	}
	va_end(cmds);
	return (cmd_head);
}

t_list	**//LEFTOFF
