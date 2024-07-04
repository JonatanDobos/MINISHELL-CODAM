#include "../minishell.h"

// LIST PRINTER!
// FOR TESTING!

static char	*type_to_char(short type)
{
	static char	arr[6][10] = {
		"NULL\0", "NO_ACTION\0", "BUILTIN\0", "PIPE\0", "REDIRECT\0", "FILE\0"};

	if (type <= 5 && type >=0)
		return (arr[type]);
	return (arr[0]);
}

void	TEST_print_pointer_arr(char **arr)
{
	size_t	i = 0;

	if (!arr || !(*arr))
		return ;
	while (arr[i] != NULL)
	{
		printf("[%2zu] %s\n", i, arr[i]);
		++i;
	}
}

void	TEST_print_string_lst(t_list **head, char *list_name)
{
	t_list	*tmp;
	int		i;

	if (!head || !(*head))
		return ;
	tmp = *head;
	i = 0;
	while (tmp != NULL)
	{
		printf("\n%s%s (%st_list%s) Node [%2i]%s\n", C_TEAL, list_name, C_DIM_RED, C_TEAL, i, C_RESET);
		printf("%s-> content:%s %s\n",C_DIM, C_RESET , (char *)tmp->content);
		tmp=tmp->next;
		++i;
	}
}

void	TEST_print_token_lst(t_shell *shell, char *list_name)
{
	t_token	**head = &shell->token_head;
	t_token	*tmp;
	int		i;

	if (!(*head))
		return ;
	tmp = *head;
	i = 0;
	while (tmp != NULL)
	{
		printf("\n%s%s Node [%2i]%s\n", C_BLUE, list_name, i, C_RESET);
		printf("%s~> type:%s %s\n", C_DIM, C_RESET, type_to_char(tmp->type));
		if (tmp->element_head)
		{
			printf("%s~> element head:%s %s, %scmd lstsize:%s %i\n", C_DIM, C_RESET, (char *)tmp->element_head->content, C_DIM, C_RESET, ft_lstsize(tmp->element_head));
			TEST_print_string_lst(&tmp->element_head, list_name);
		}
		else
			printf("%s~> element head:%s NULL\n", C_DIM, C_RESET);
		printf("%s~> cmd arr:%s\n", C_DIM, C_RESET);
		TEST_print_pointer_arr(tmp->cmd_array);
		tmp=tmp->next;
		++i;
	}
}
