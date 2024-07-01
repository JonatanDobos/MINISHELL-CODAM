#include "../minishell.h"

// LIST PRINTER!
// FOR TESTING!

static char	*token_to_char(short token)
{
	static char	arr[6][10] = {
		"NO_ACTION\0", "BUILTIN\0", "PIPE\0", "REDIRECT\0", "FILE\0", (char *)NULL};

	return (arr[token]);
}

void	TEST_print_pointer_arr(char **arr)
{
	size_t	i = 0;

	if (!arr || !(*arr))
		return ;
	while (arr[i] != NULL)
	{
		printf("[%2i] %s\n", i, arr[i]);
		++i;
	}
}

void	TEST_print_string_lst(t_list **head)
{
	t_list	*tmp;
	int		i;

	if (!head || !(*head))
		return ;
	tmp = *head;
	i = 0;
	while (tmp != NULL)
	{
		printf("\n%sstring Node [%2i]%s\n",C_TEAL, i, C_RESET);
		printf("-> data: %s\n", tmp->data);
		tmp=tmp->next;
		++i;
	}
}

void	TEST_print_sig_arg_lst(t_sig_arg **head)
{
	t_sig_arg	*tmp;
	int				i;

	if (!head || !(*head))
		return ;
	tmp = *head;
	i = 0;
	while (tmp != NULL)
	{
		printf("\n%ssig_arg Node [%2i]%s\n",C_TEAL, i, C_RESET);
		printf("-> token: %s\n", token_to_char(tmp->token));
		printf("-> cmd head: %s, cmd lstsize: %i\n", (*(tmp->cmd_head))->data, ft_lstsize(*(tmp->cmd_head)));
		printf("-> cmd arr:\n");
		TEST_print_pointer_arr(tmp->cmd_array);
		tmp=tmp->next;
		++i;
	}
}
