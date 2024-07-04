#include "../minishell.h"

// LIST PRINTER!
// FOR TESTING!

// TESTING Colors (_TEST.c)

#define C_DIM		"\033[0m\033[2m"
#define C_ITALIC	"\033[0m\033[3m"

#define C_DIM_RED	"\033[0m\033[2;31m"
#define C_DIM_PURP	"\033[0m\033[2;35m"
#define C_DIM_TEAL	"\033[0m\033[2;36m"
#define C_DIM_GREEN	"\033[0m\033[2;32m"

#define C_TEAL		"\033[0m\033[0;36m"
#define C_BLACK		"\033[0m\033[0;30m"
#define C_GREEN		"\033[0m\033[0;32m"
#define C_BLUE		"\033[0m\033[0;34m"
#define C_PURPLE	"\033[0m\033[0;35m"
#define C_WHITE		"\033[0m\033[0;37m"

static char	*type_to_char(short type)
{
	static char	*err = "NON_VALID\0";
	static char	arr[5][10] = {
		"NO_ACTION\0", "BUILTIN\0", "PIPE\0", "REDIRECT\0", "FILE\0"};

	if (type <= 5 && type >=0)
		return (arr[type]);
	return (err);
}

void	TEST_print_pointer_arr(
	char **arr, char *precursor, char *pre_col, char *accent_col, char *name)
{
	int	i = 0;

	if (!arr || !(*arr))
		return ;
	if (!accent_col)
		accent_col = C_RESET;
	if (!pre_col)
		pre_col = C_RESET;
	if (!precursor)
		precursor = "\0";
	printf("%s%s%s\n", pre_col, precursor, C_RESET);
	if (name)// print array name
	{
		printf("%s%s", pre_col, precursor);
		printf("%s%s", accent_col, name);
		printf("%s[]%s\n", C_YELLOW, C_RESET);
	}
	while (arr[i] != NULL)// print array
	{
		printf("%s%s", pre_col, precursor);
		printf("%s|", accent_col);
		printf("%s[%s%i%s]: ", C_DIM, C_TEAL, i, C_DIM);
		printf("%s%s\n", C_RESET, arr[i]);
		++i;
	}
	printf("%s%s%s\n", pre_col, precursor, C_RESET);
}

void	TEST_print_elem_list(t_shell *shell)
{
	char	*accent = C_TEAL;
	char	*name = "Line Element";

	TEST_print_t_list(&shell->line_element_head, NULL, NULL, accent, name);
}

void	TEST_print_t_list(
	t_list **head, char *precursor, char *pre_col, char *accent_col, char *list_name)
{
	t_list	*tmp;
	int		i;

	if (!head || !(*head))
		return ;
	tmp = *head;
	i = 0;
	if (!accent_col)
		accent_col = C_RESET;
	if (!pre_col)
		pre_col = C_RESET;
	if (!precursor)
		precursor = "\0";
	printf("%s%s%s\n", pre_col, precursor, C_RESET);
	if (list_name)// print list name
	{
		printf("%s%s", pre_col, precursor);
		printf("%s%s ", accent_col, list_name);
	}
	printf("(%st_list%s) ", C_DIM_RED, accent_col);
	printf(":: %s%i%s\n) ", C_PURPLE, ft_lstsize(*head), C_RESET);
	while (tmp != NULL)// print list content
	{
		printf("%s%s", pre_col, precursor);
		printf("%s|", accent_col);
		printf("%s[%s%i%s]: ", C_DIM, C_PURPLE, i, C_DIM);
		printf("%s%s\n", C_RESET, tmp->content);
		tmp=tmp->next;
		++i;
	}
	printf("%s%s%s\n", pre_col, precursor, C_RESET);
}

void	TEST_print_token_lst(t_shell *shell, char *name)
{
	t_token	*tmp;
	int		i;

	tmp = shell->token_head;
	i = 0;
	while (tmp != NULL)
	{
		printf("\n%s%s%s ", C_PURPLE, name, C_BLUE);
		printf("[%s%i%s]%s\n",C_YELLOW, C_BLUE, i, C_RESET);
		printf("%s|", C_BLUE);
		printf("%s > type:%s %s\n", C_DIM, C_RESET, type_to_char(tmp->type));
		if (tmp->element_head)
		{
			printf("%s|", C_BLUE);
			TEST_print_t_list(&tmp->element_head, "|", C_BLUE, C_DIM_TEAL, "element_head");
		}
		else
		{
			printf("%s|", C_BLUE);
			printf("%s > element head:%s NULL\n", C_DIM_TEAL, C_RESET);
		}
		TEST_print_pointer_arr(tmp->cmd_array, "|", C_BLUE, C_DIM_RED, "cmd_array");
		tmp=tmp->next;
		++i;
	}
}
