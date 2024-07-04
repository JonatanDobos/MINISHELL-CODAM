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

// Inits precursor set, takes unsigned char!
static void	precursor_set(
	t_uchar *set, int precursor_symbol, int optional_folowup_char)
{
	set[0] = (t_uchar)precursor_symbol;
	set[1] = (t_uchar)optional_folowup_char;
	set[2] = '\0';
}

// RETURN: (char *)name corresponding to type enum
static char	*type_to_char(short type)
{
	static char	*err = "NON_VALID\0";
	static char	arr[5][10] = {
		"NO_ACTION\0", "BUILTIN\0", "PIPE\0", "REDIRECT\0", "FILE\0"};

	if (type <= 5 && type >=0)
		return (arr[type]);
	return (err);
}

// Prints out pointer array
void	TEST_print_pointer_arr(
	char **arr,
	char *precursor,
	char *pre_col,
	char *accent_col,
	char *name)
{
	int		i = 0;
	t_uchar	set[3];

	if (!arr || !(*arr))
		return ;
	precursor_set(set, '|', ' ');
	if (!accent_col)
		accent_col = C_RESET;
	if (!pre_col)
		pre_col = C_RESET;
	if (!precursor)
		precursor = "\0";
	if (name)// print array name
	{
		printf("%s%s", pre_col, precursor);
		printf("%s> %s", accent_col, name);
		printf("%s[]%s\n", C_YELLOW, C_RESET);
	}
	while (arr[i] != NULL)// print array
	{
		printf("%s%s", pre_col, precursor);
		printf("%s%s", accent_col, set);
		printf("%s[%s%i%s]: ", accent_col, C_DIM_TEAL, i, accent_col);
		printf("%s%s\n", C_WHITE, arr[i]);
		++i;
	}
}

// Prints out line_element list
void	TEST_print_elem_list(t_shell *shell)
{
	char	*accent = C_TEAL;
	char	*name = "Line Element";

	printf("\n");
	TEST_print_t_list(&shell->line_element_head, NULL, NULL, accent, name);
	printf("\n");
}

// Prints out t_list list
void	TEST_print_t_list(
	t_list **head,
	char *precursor,
	char *pre_col,
	char *accent_col,
	char *list_name)
{
	t_list	*tmp;
	int		i;
	t_uchar	set[3];

	if (!head || !(*head))
		return ;
	tmp = *head;
	i = 0;
	precursor_set(set, '|', ' ');
	if (!accent_col)
		accent_col = C_RESET;
	if (!pre_col)
		pre_col = C_RESET;
	if (!precursor)
		precursor = "\0";
	if (list_name)// print list name
	{
		printf("%s%s", pre_col, precursor);
		printf("%s> %s ", accent_col, list_name);
	}
	printf("(%st_list%s) ", C_DIM_RED, accent_col);
	printf(":: %s%i%s\n", C_PURPLE, ft_lstsize(*head), C_RESET);
	while (tmp != NULL)// print list content
	{
		printf("%s%s", pre_col, precursor);
		printf("%s%s", accent_col, set);
		printf("%s[%s%i%s]: ", accent_col, C_DIM_TEAL, i, accent_col);
		printf("%s%s\n", C_WHITE, (char *)tmp->content);
		tmp=tmp->next;
		++i;
	}
	printf("%s", C_RESET);
}

// Prints out token list
void	TEST_print_token_lst(t_shell *shell, char *name)
{
	t_token	*tmp;
	int		i;
	t_uchar	set[3];

	tmp = shell->token_head;
	i = 0;
	precursor_set(set, '|', ' ');
	printf("%s\\/%s", C_GREEN, C_RESET);
	while (tmp != NULL)
	{
		printf("\n%s%s%s ", C_PURPLE, name, C_BLUE);
		printf("{%s%i%s}%s\n",C_YELLOW, i, C_BLUE, C_RESET);
		printf("%s%s", C_PURPLE, set);
		printf("%s> type:%s %s\n", C_DIM_PURP, C_WHITE, type_to_char(tmp->type));
		if (tmp->element_head)
			TEST_print_t_list(&tmp->element_head, set, C_PURPLE, C_BLUE, "element_head");
		else
		{
			printf("%s%s", C_PURPLE, set);
			printf("%s> element_head:%s NULL\n", C_DIM, C_WHITE);
		}
		if (tmp->cmd_array && *tmp->cmd_array)
			TEST_print_pointer_arr(tmp->cmd_array, set, C_PURPLE, C_DIM_TEAL, "cmd_array");
		else
		{
			printf("%s%s", C_PURPLE, set);
			printf("%s> cmd_array:%s NULL\n", C_DIM, C_WHITE);
		}
		tmp=tmp->next;
		++i;
	}
	printf("%s/\\%s", C_GREEN, C_RESET);
}
