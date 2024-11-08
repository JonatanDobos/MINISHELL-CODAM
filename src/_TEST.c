#include "../minishell.h"

// LIST PRINTER!
// FOR TESTING!

// symbol color -> thick_line color
static char	*to_bg_color(const char *color)
{
	if (!ft_strncmp(color, C_TEAL, ft_strlen(color)) || !ft_strncmp(color, C_DIM_TEAL, ft_strlen(color)))
		return (C_BG_CYAN);
	if (!ft_strncmp(color, C_GREEN, ft_strlen(color)) || !ft_strncmp(color, C_DIM_GREEN, ft_strlen(color)))
		return (C_BG_GREEN);
	if (!ft_strncmp(color, C_BLUE, ft_strlen(color)))
		return (C_BG_BLUE);
	if (!ft_strncmp(color, C_RED, ft_strlen(color)) || !ft_strncmp(color, C_DIM_RED, ft_strlen(color)))
		return (C_BG_RED);
	if (!ft_strncmp(color, C_PURPLE, ft_strlen(color)) || !ft_strncmp(color, C_DIM_PURP, ft_strlen(color)))
		return (C_BG_PURPLE);
	if (!ft_strncmp(color, C_WHITE, ft_strlen(color)) || !ft_strncmp(color, C_B_WHITE, ft_strlen(color)))
		return (C_BG_WHITE);
	else
		return (C_BG_BLACK);
}

static void	print_precursor(char *set, char *color, bool thick_line)
{
	if (!thick_line)
		printf("%s%s", color, set);
	else
		printf("%s%c%s%c", to_bg_color(color), set[0], C_RESET, set[1]);
}

// Inits precursor set, takes unsigned char!
static void	precursor_set(
	char *set, int precursor_symbol, int optional_folowup_char)
{
	set[0] = (char)precursor_symbol;
	set[1] = (char)optional_folowup_char;
	set[2] = '\0';
}

// RETURN: (char *)name corresponding to type enum
static char	*type_to_char(short type)
{
	static char	arr[4][10] = {
		"T_SYS_CMD\0", "BUILTIN\0", "PIPE\0", "REDIRECT\0"};

	if (type <= 5 && type >=0)
		return (arr[type]);
	return (NULL);
}

// Prints out semicol_pos array
void	TEST_print_pointer_arr(
	char **arr,
	char *precursor,
	char *pre_col,
	bool thick_line,
	char *accent_col,
	char *name)
{
	int		i = 0;
	char	set[3];

	if (!arr || !(*arr))
		return ;
	if (thick_line)
		precursor_set(set, ' ', ' ');// inits precursor characters
	else
		precursor_set(set, '|', ' ');// inits precursor characters
	if (!accent_col)
		accent_col = C_RESET;
	if (!pre_col)
		pre_col = C_RESET;
	if (!precursor)
		precursor = "\0";
	if (name)// print array name
	{
		print_precursor(precursor, pre_col, thick_line);
		printf("%s> %s", accent_col, name);
		printf("%s[]%s\n", C_YELLOW, C_RESET);
	}
	while (arr[i] != NULL)// print array
	{
		print_precursor(precursor, pre_col, thick_line);
		print_precursor(set, accent_col, thick_line);
		printf("%s[%s%i%s]: ", accent_col, C_DIM_TEAL, i, accent_col);
		printf("%s|", C_DIM_TEAL);
		printf("%s%s", C_B_WHITE, arr[i]);
		printf("%s|\n", C_DIM_TEAL);
		++i;
	}
	printf("%s", C_RESET);
}

// Prints out line_element list
void	TEST_print_elem_list(t_shell *shell, char *accent_col, bool thick_line, char *name)
{
	printf("\n");
	TEST_print_t_list(&shell->line_element_head, NULL, NULL, thick_line, accent_col, name);
	printf("\n");
}

// Prints out t_list list
void	TEST_print_t_list(
	t_list **head,
	char *precursor,
	char *pre_col,
	bool thick_line,
	char *accent_col,
	char *list_name)
{
	t_list	*tmp;
	int		i;
	char	set[3];

	if (!head || !(*head))
		return ;
	tmp = *head;
	i = 0;
	if (thick_line)
		precursor_set(set, ' ', ' ');// inits precursor characters
	else
		precursor_set(set, '|', ' ');// inits precursor characters
	if (!accent_col)
		accent_col = C_RESET;
	if (!pre_col)
		pre_col = C_RESET;
	if (!precursor)
		precursor = (char *)"\0";
	if (list_name)// print list name
	{
		print_precursor(precursor, pre_col, thick_line);
		printf("%s> %s ", accent_col, list_name);
	}
	printf("(%st_list%s) ", C_DIM_RED, accent_col);
	printf(":: %s%i%s\n", C_PURPLE, ft_lstsize(*head), C_RESET);
	while (tmp != NULL)// print list content
	{
		print_precursor(precursor, pre_col, thick_line);
		print_precursor(set, accent_col, thick_line);
		printf("%s[%s%i%s]: ", accent_col, C_DIM_TEAL, i, accent_col);
		printf("%s|", C_DIM_TEAL);
		printf("%s%s", C_B_WHITE, (char *)tmp->content);
		printf("%s|\n", C_DIM_TEAL);
		tmp=tmp->next;
		++i;
	}
	printf("%s", C_RESET);
}

// Prints out token list
// thick_line: true = precursor bg is colored, false = prec symbol is colored
void	TEST_print_token_lst(
	t_shell *shell, char *accent_col, bool thick_line, char *name)
{
	t_token	*tmp;
	int		i;
	char	set[3];

	tmp = shell->token_head;
	i = 0;
	if (thick_line)
		precursor_set(set, ' ', ' ');// inits precursor characters
	else
		precursor_set(set, '|', ' ');// inits precursor characters
	printf("%s\\/%s", C_GREEN, C_RESET);
	while (tmp != NULL)
	{
		printf("\n%s%s%s ", accent_col, name, C_BLUE);// name
		printf("{%s%i%s}%s\n",C_YELLOW, i, C_BLUE, C_RESET);// index
		print_precursor(set, accent_col, thick_line);// precursor
		printf("%s> type:%s %s\n", C_DIM_GREEN, C_B_WHITE, type_to_char(tmp->type));// ->type
		// if (tmp->element_head)
		// 	TEST_print_t_list(&tmp->element_head, set, accent_col, thick_line, C_BLUE, "element_head");// ->elem_head
		// else
		// {
		// 	print_precursor(set, accent_col, thick_line);
		// 	printf("%s> element_head: NULL\n", C_DIM);
		// }
		if (tmp->cmd_array)
			TEST_print_pointer_arr(tmp->cmd_array, set, accent_col, thick_line, C_DIM_TEAL, "cmd_array");// ->cmd_head
		if (tmp->cmd_array)
			TEST_print_pointer_arr(tmp->redirect, set, accent_col, thick_line, "\e[2;33m", "redirect");// ->redirect
		else
		{
			print_precursor(set, accent_col, thick_line);
			printf("%s> cmd_array: NULL\n", C_DIM);
		}
		tmp=tmp->next;
		++i;
	}
	printf("%s/\\%s\n", C_GREEN, C_RESET);
}
