#include "../minishell.h"

// ik denk dat infile en outfile handling kan gebeuren voor alle builtins
// INPUT: output_file = NULL -> prints to STDOUT
// EXITS on failure
void	builtin_echo(t_shell *shell, t_token *token, char *output_file)
{
	t_list	*tmp;
	int		fd;

	if (!token || !token->element_head)
		return ;
	if (output_file != NULL) // redirects will be handled elsewhere
	{
		fd = open_outputfile(output_file);
		if (fd == -1)
			exit_clean(shell, errno, "builtin echo open");
		if (!set_output(fd))
			exit_clean(shell, errno, "builtin echo set");
	}
	tmp = token->element_head->next;
	while (tmp != NULL)
	{
		printf("%s", (char *)tmp->content);
		if (tmp->next != NULL)
			printf(" ");
		tmp = tmp->next;
	}
	printf("\n");
	if (output_file != NULL)
		if (!set_output(STDOUT_FILENO))
			exit_clean(shell, errno, "builtin echo set 2");
}
