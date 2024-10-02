#include "../minishell.h"

bool	istoken(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
