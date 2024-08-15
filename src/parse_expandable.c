#include "../minishell.h"

// Parses for envariable corresponding to envkey.
// RETURN: shell->envp[corresponding index] (non malloced char *)
char	*parse_envp(
	char **envp, char *str, size_t i)
{
	size_t	start;
	size_t	len;
	size_t	j;

	if (str[i] != '$' || !ft_isalnum(str[i + 1]))
		return (NULL);
	start = ++i;
	while (str[i] == '_' || ft_isalnum(str[i]))
		++i;
	len = i - start;
	j = 0;
	while (envp[j] != NULL)
	{
		if (!ft_strncmp(str + start, envp[j], len)
			&& envp[j][len] == '=')
			break ;
		++j;
	}
	if (envp[j] == NULL)
		return (NULL);
	return (ft_strchr(envp[j], '=') + 1);
}

// Returns NULL on failure
char	*insert_envp_in_str(t_shell *shell, char *str, size_t i)
{
	char	*ret;
	char	*envp_str;
	size_t	len_del;

	if (str[i + 1] == '?')
		ret = str_insert(str, ft_itoa(shell->last_errno), i, 2);
	else
	{
		len_del = i + 1;
		while (str[len_del] == '_' || ft_isalnum(str[len_del]))
			++len_del;
		len_del = len_del - i;
		envp_str = parse_envp(shell->envp, str, i);
		if (envp_str)
			ret = str_insert(str, envp_str, i, len_del);
		else
			ret = str_insert(str, "\0", i, len_del);
	}
	return (ret);
}

// Expands envp inside string
// used in double quotes
// *str is freed inside function
char	*expand_env_in_str(t_shell *shell, char *str)
{
	size_t	i;
	char	*ret;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			ret = insert_envp_in_str(shell, str, i);
			free(str);
			if (!ret)
				exit_clean(shell, errno, "expand_envp_in_str");
			str = ret;
			ret = NULL;
		}
		++i;
	}
	return (str);
}
