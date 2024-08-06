#include "../minishell.h"

// don't know what to check before testing execution; some things are better unchecked to be handled later
// rn I call builtin syntax from inside the builtin_ functions

// enter specific syntax check function based on token type (utils_syntax.c)
static bool syntax_token(t_token *token)
{
	if ((token->type == T_BUILTIN
		&& syntax_builtin(token->element_head) == false)
		|| (token->type == T_PIPE
		&& syntax_pipe(token->element_head) == false)
		|| (token->type == T_REDIRECT
		&& syntax_redirect(token->element_head) == false)
		|| (token->type == T_FILE
		&& syntax_file(token->element_head) == false))
		return (false);
	return (true);
}

// see if the construction of elements corresponds to token type
bool	syntax_post(t_shell *shell)
{
	return (true); // bypassing until syntax check necessary
	t_token	*current;

	current = shell->token_head;
	while (current != NULL)
	{
		if (syntax_token(current) == false)
			return (false);
		current = current->next;
	}
}
