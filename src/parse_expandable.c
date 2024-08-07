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
	while (str[i] && (str[i] == '_'
			|| ft_isalnum(str[i])))
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
	return (envp[j]);
}

// Returns:
// - copy of *str with str[start] -> str[start + len_del] replaced by *insert
// - *str when input is incufficient
// - NULL on malloc failure
char	*str_insert(char *str, char *insert, size_t start, size_t len_del)
{
	size_t	i;
	size_t	j;
	char	*ret;

	if (!str || !insert || start > ft_strlen(str) || \
	len_del > ft_strlen_null(str) - start)
		return (str);
	ret = (char *)malloc((ft_strlen(str) - len_del) + ft_strlen(insert) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (i < start)
		ret[i++] = str[j++];
	j = 0;
	while (insert[j])
		ret[i++] = insert[j++];
	j = start + len_del;
	while (str[j])
		ret[i++] = str[j++];
	ret[i] = '\0';
	return (ret);
}

// Returns NULL on failure
char	*insert_envp_in_str(t_shell *shell, char *str, size_t i)
{
	char	*ret;
	char	*envp_str;
	size_t	len_del;

	if (str[i + 1] == '?' && (ft_iswhitespace(str[i + 2]) || !str[i + 2]))
		ret = str_insert(str, ft_itoa(shell->last_errno), i, 2);
	else
	{
		envp_str = parse_envp(shell->envp, str, i);
		if (envp_str)
		{
			len_del = i;
			while (str[len_del] && !ft_iswhitespace(str[len_del]))
				++len_del;
			len_del = len_del - i;
			ret = str_insert(str, ft_strchr(envp_str, '=') + 1, i, len_del);
		}
		else
			return (str);
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
			if (!ret)
			{
				free(str);
				exit_clean(shell, errno, "expand_envp_in_str");
			}
			if (ft_strncmp(str, ret, ft_strlen(str) + 1))
			{
				free(str);
				str = ret;
			}
			ret = NULL;
			printf("TEST> [%zu] %s\n", i, str);// TEST
		}
		++i;
	}
	return (str);
}
