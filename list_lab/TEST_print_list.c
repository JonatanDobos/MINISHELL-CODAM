#include "list_types.h"

// FOR TESTING!

static char	*token_to_char(short token)
{
	static char	arr[6][10] = {
		"NO_ACTION\0", "BUILTIN\0", "PIPE\0", "REDIRECT\0", "FILE\0", (char *)NULL};

	return (arr[token]);
}

static void	print_string_lst(t_list **head)
{
	t_list	*tmp;
	int		i;

	tmp = *head;
	i = 0;
	while (tmp != NULL)
	{
		printf("\nNode %i\n", i);
		printf("-> data: %s\n", tmp->data);
		tmp=tmp->next;
		++i;
	}
}

static void	print_token_lst(t_token_node **head)
{
	t_token_node	*tmp;
	int				i;

	tmp = *head;
	i = 0;
	while (tmp != NULL)
	{
		printf("\nNode %i\n", i);
		printf("-> token: %s\n", token_to_char(tmp->token));
		printf("-> cmd: %s\n", (*(tmp->element_head))->data);
		tmp=tmp->next;
		++i;
	}
}

bool	TEST_print_lst(void **head, t_getnext_func getnext)
{
	if (!head || !(*head))
		return (printf("No list\n"), false);
	if (getnext == getnext_string)
		print_string_lst(head);
	else if (getnext == getnext_token)
		print_token_lst(head);
	return (true);
}
